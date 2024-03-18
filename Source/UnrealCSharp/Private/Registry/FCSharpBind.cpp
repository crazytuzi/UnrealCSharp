#include "Registry/FCSharpBind.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FCSharpInvoker.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Template/TGetArrayLength.inl"
#include "Setting/UnrealCSharpSetting.h"

#if !WITH_EDITOR
TSet<TWeakObjectPtr<UStruct>> FCSharpBind::NotOverrideTypes;
#endif

FCSharpBind::FCSharpBind()
{
	Initialize();
}

FCSharpBind::~FCSharpBind()
{
	Deinitialize();
}

void FCSharpBind::Initialize()
{
	OnCSharpEnvironmentInitializeDelegateHandle = FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.AddRaw(
		this, &FCSharpBind::OnCSharpEnvironmentInitialize);
}

void FCSharpBind::Deinitialize()
{
	if (OnCSharpEnvironmentInitializeDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.Remove(OnCSharpEnvironmentInitializeDelegateHandle);
	}
}

MonoObject* FCSharpBind::Bind(FDomain* InDomain, UObject* InObject)
{
	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
	{
		return FoundMonoObject;
	}

	return Bind(InDomain, InObject, false) ? FCSharpEnvironment::GetEnvironment().GetObject(InObject) : nullptr;
}

MonoObject* FCSharpBind::Bind(FDomain* InDomain, UClass* InClass)
{
	Bind(InDomain, InClass, false);

	return Bind(InDomain, static_cast<UObject*>(InClass));
}

bool FCSharpBind::Bind(FDomain* InDomain, UObject* InObject, const bool bNeedMonoClass)
{
	return BindImplementation(InDomain, InObject, bNeedMonoClass);
}

bool FCSharpBind::Bind(FDomain* InDomain, UStruct* InStruct, const bool bNeedMonoClass)
{
	if (FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InStruct))
	{
		return true;
	}

	if (bNeedMonoClass && !CanBind(InDomain, InStruct))
	{
#if !WITH_EDITOR
		NotOverrideTypes.Add(InStruct);
#endif

		return false;
	}

	return BindImplementation(InDomain, InStruct);
}

bool FCSharpBind::Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	return BindImplementation(InDomain, InMonoObject, InStructName);
}

bool FCSharpBind::Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	return BindImplementation(InClassDescriptor, InClass, InFunction);
}

bool FCSharpBind::BindClassDefaultObject(FDomain* InDomain, UObject* InObject)
{
	if (CanBind(InDomain, InObject->GetClass()))
	{
		FClassRegistry::AddClassConstructor(InObject->GetClass());

		Bind(InDomain, InObject);

		return true;
	}
	else
	{
		if (const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>())
		{
			for (const auto& BindClass : UnrealCSharpSetting->GetBindClass())
			{
				if (InObject->IsA(BindClass.Class))
				{
					return BindClass.bNeedMonoClass ? false : Bind(InDomain, InObject, false);
				}
			}
		}
	}

	return false;
}

bool FCSharpBind::BindImplementation(FDomain* InDomain, UObject* InObject, const bool bNeedMonoClass)
{
	if (InDomain == nullptr || InObject == nullptr)
	{
		return false;
	}

	const auto InClass = InObject->GetClass();

	if (InClass == nullptr)
	{
		return false;
	}

	if (!Bind(InDomain, InClass, bNeedMonoClass))
	{
		return false;
	}

	const auto FoundClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(InClass);

	if (FoundClassDescriptor == nullptr)
	{
		return false;
	}

	const auto FoundMonoClass = FoundClassDescriptor->GetMonoClass();

	if (FoundMonoClass == nullptr)
	{
		return false;
	}

	const auto NewMonoObject = InDomain->Object_New(FoundMonoClass);

	FCSharpEnvironment::GetEnvironment().AddObjectReference(InObject, NewMonoObject);

	return true;
}

bool FCSharpBind::BindImplementation(FDomain* InDomain, UStruct* InStruct)
{
	if (InDomain == nullptr || InStruct == nullptr)
	{
		return false;
	}

	auto SuperStruct = InStruct->GetSuperStruct();

	while (SuperStruct != nullptr)
	{
		Bind(InDomain, SuperStruct, false);

		SuperStruct = SuperStruct->GetSuperStruct();
	}

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment().AddClassDescriptor(InDomain, InStruct);

	if (NewClassDescriptor == nullptr)
	{
		return false;
	}

	for (TFieldIterator<FProperty> It(InStruct, EFieldIteratorFlags::ExcludeSuper,
	                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
	{
		if (const auto Property = *It)
		{
			if (!NewClassDescriptor->HasPropertyDescriptor(Property->GetFName()))
			{
				if (const auto FoundClassField = InDomain->Self_Class_Get_Field_From_Name(
					NewClassDescriptor->GetMonoClass(), TCHAR_TO_UTF8(*FString::Printf(TEXT(
							"__%s"
						),
						*FUnrealCSharpFunctionLibrary::Encode(Property->GetName())
					))))
				{
					auto PropertyHash = GetTypeHash(Property);

					InDomain->Field_Static_Set_Value(InDomain->Class_VTable(NewClassDescriptor->GetMonoClass()),
					                                 FoundClassField, &PropertyHash);

					FCSharpEnvironment::GetEnvironment().AddPropertyHash(
						PropertyHash, NewClassDescriptor, Property->GetFName());
				}
			}
		}
	}

	if (const auto InClass = Cast<UClass>(InStruct))
	{
		if (const auto FoundMonoClass = InDomain->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct),
			FUnrealCSharpFunctionLibrary::GetFullClass(InStruct)))
		{
			TMap<FName, UFunction*> Functions;

			for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
			{
				if (const auto Function = *It)
				{
					Functions.Add(Function->GetFName(), Function);
				}
			}

			for (const auto& Interface : InClass->Interfaces)
			{
				for (TFieldIterator<UFunction> It(Interface.Class, EFieldIteratorFlags::ExcludeSuper,
				                                  EFieldIteratorFlags::ExcludeDeprecated,
				                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
				{
					if (const auto Function = InClass->FindFunctionByName(It->GetFName()))
					{
						Functions.Add(Function->GetFName(), Function);
					}
				}
			}

			for (const auto& FunctionPair : Functions)
			{
				if (const auto FoundClassField = InDomain->Self_Class_Get_Field_From_Name(
					NewClassDescriptor->GetMonoClass(), TCHAR_TO_UTF8(*FString::Printf(TEXT(
							"__%s"
						),
						*FUnrealCSharpFunctionLibrary::Encode(FunctionPair.Key.ToString())
					))))
				{
					auto FunctionHash = GetTypeHash(FunctionPair.Value);

					InDomain->Field_Static_Set_Value(
						InDomain->Class_VTable(NewClassDescriptor->GetMonoClass()),
						FoundClassField, &FunctionHash);

					FCSharpEnvironment::GetEnvironment().AddFunctionHash(
						FunctionHash, NewClassDescriptor, FunctionPair.Key);
				}
			}

			Functions.Empty();

			for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::IncludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
			{
				if (auto Function = *It)
				{
					if (Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) && !Function->HasAnyFunctionFlags(FUNC_Final)
						&& !Functions.Contains(Function->GetFName()))
					{
						Functions.Emplace(Function->GetName(), Function);
					}
				}
			}

			for (const auto& FunctionPair : Functions)
			{
				if (const auto FoundMonoMethod = InDomain->Class_Get_Method_From_Name(
					FoundMonoClass, FUnrealCSharpFunctionLibrary::Encode(FunctionPair.Key.ToString()),
					FunctionPair.Value->ReturnValueOffset != MAX_uint16
						? FunctionPair.Value->NumParms - 1
						: FunctionPair.Value->NumParms))
				{
					if (IsOverrideMethod(InDomain,
					                     InDomain->Method_Get_Object(FoundMonoMethod, FoundMonoClass)))
					{
						Bind(NewClassDescriptor, InClass, FunctionPair.Value);
					}
				}
			}
		}
	}

	return true;
}

bool FCSharpBind::BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	if (InClassDescriptor == nullptr || InClass == nullptr || InFunction == nullptr)
	{
		return false;
	}

	if (InClassDescriptor->HasFunctionDescriptor(GetTypeHash(InFunction)))
	{
		return false;
	}

	const auto OriginalFunction = GetOriginalFunction(InClassDescriptor, InFunction);

	if (OriginalFunction == nullptr)
	{
		return false;
	}

	const auto FunctionName = OriginalFunction->GetFName();

	if (OriginalFunction->GetOuter() == InClass)
	{
		const auto NewFunctionDescriptor = new FCSharpFunctionDescriptor(OriginalFunction);

		const auto FunctionHash = GetTypeHash(NewFunctionDescriptor);

		InClassDescriptor->FunctionHashSet.Add(FunctionHash);

		FCSharpEnvironment::GetEnvironment().AddFunctionDescriptor(FunctionHash, NewFunctionDescriptor);

		const FName NewFunctionName(*FString::Printf(TEXT("%s%s"), *FunctionName.ToString(), TEXT("_Original")));

		NewFunctionDescriptor->OriginalFunctionFlags = OriginalFunction->FunctionFlags;

		NewFunctionDescriptor->OriginalNativeFuncPtr = OriginalFunction->GetNativeFunc();

		NewFunctionDescriptor->OriginalScript = OriginalFunction->Script;

		NewFunctionDescriptor->OriginalFunction = DuplicateFunction(OriginalFunction, InClass, NewFunctionName);

		UpdateCallCSharpFunction(OriginalFunction);
	}
	else
	{
		auto NewFunction = InClass->FindFunctionByName(FunctionName, EIncludeSuperFlag::ExcludeSuper);

		if (NewFunction != nullptr)
		{
			return false;
		}

		NewFunction = DuplicateFunction(OriginalFunction, InClass, FunctionName);

		const auto NewFunctionDescriptor = new FCSharpFunctionDescriptor(NewFunction);

		const auto FunctionHash = GetTypeHash(NewFunctionDescriptor);

		InClassDescriptor->FunctionHashSet.Add(FunctionHash);

		FCSharpEnvironment::GetEnvironment().AddFunctionDescriptor(FunctionHash, NewFunctionDescriptor);

		NewFunctionDescriptor->OriginalFunction = OriginalFunction;

		UpdateCallCSharpFunction(NewFunction);
	}

	return true;
}

bool FCSharpBind::BindImplementation(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *InStructName.ToString());

	if (InDomain == nullptr || InScriptStruct == nullptr)
	{
		return false;
	}

	if (!Bind(InDomain, InScriptStruct, false))
	{
		return false;
	}

	const auto StructureSize = InScriptStruct->GetStructureSize() ? InScriptStruct->GetStructureSize() : 1;

	const auto Structure = static_cast<void*>(static_cast<uint8*>(FMemory::Malloc(StructureSize)));

	InScriptStruct->InitializeStruct(Structure);

	FCSharpEnvironment::GetEnvironment().AddStructReference(InScriptStruct, Structure, InMonoObject);

	return true;
}

bool FCSharpBind::CanBind(const FDomain* InDomain, UStruct* InStruct)
{
#if !WITH_EDITOR
	if (NotOverrideTypes.Contains(InStruct))
	{
		return false;
	}
#endif

	if (const auto FoundMonoClass = InDomain->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct),
		FUnrealCSharpFunctionLibrary::GetFullClass(InStruct)))
	{
		if (const auto FoundMonoType = InDomain->Class_Get_Type(FoundMonoClass))
		{
			if (const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
				FoundMonoType))
			{
				return IsOverrideType(InDomain, FoundReflectionType);
			}
		}
	}

	return false;
}

UFunction* FCSharpBind::GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction)
{
	if (InClassDescriptor == nullptr || InFunction == nullptr)
	{
		return nullptr;
	}

	if (!IsCallCSharpFunction(InFunction))
	{
		return InFunction;
	}

	const auto FoundFunctionDescriptor = InClassDescriptor->GetOrAddFunctionDescriptor(InFunction->GetFName());

	const auto OriginalFunction = FoundFunctionDescriptor != nullptr
		                              ? FoundFunctionDescriptor->OriginalFunction.Get()
		                              : nullptr;

	if (OriginalFunction != nullptr && !IsCallCSharpFunction(OriginalFunction))
	{
		return OriginalFunction;
	}

	const auto SuperClass = InFunction->GetOuterUClass()->GetSuperClass();

	const auto SuperOriginalFunction = SuperClass != nullptr
		                                   ? SuperClass->FindFunctionByName(InFunction->GetFName())
		                                   : nullptr;

	return GetOriginalFunction(InClassDescriptor, SuperOriginalFunction);
}

bool FCSharpBind::IsCallCSharpFunction(UFunction* InFunction)
{
	return InFunction && (InFunction->GetNativeFunc() == &FCSharpInvoker::execCallCSharp) && (InFunction->Script.Num() >
		0) && (InFunction->Script[0] == EX_CallCSharp);
}

UFunction* FCSharpBind::DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName)
{
	if (InOriginalFunction == nullptr || InClass == nullptr)
	{
		return nullptr;
	}

	const auto OriginalFunctionFlags = InOriginalFunction->FunctionFlags;

	InOriginalFunction->FunctionFlags &= (~EFunctionFlags::FUNC_Native);

	FObjectDuplicationParameters ObjectDuplicationParameters(InOriginalFunction, InClass);

	ObjectDuplicationParameters.DestName = InFunctionName;

	ObjectDuplicationParameters.InternalFlagMask &= (~EInternalObjectFlags::Native);

	const auto NewFunction = Cast<UFunction>(StaticDuplicateObjectEx(ObjectDuplicationParameters));

	InOriginalFunction->FunctionFlags = OriginalFunctionFlags;

	if (NewFunction == nullptr)
	{
		return nullptr;
	}

	NewFunction->FunctionFlags = OriginalFunctionFlags;

	NewFunction->SetNativeFunc(InOriginalFunction->GetNativeFunc());

	NewFunction->StaticLink(true);

	InClass->AddFunctionToFunctionMap(NewFunction, InFunctionName);

	NewFunction->ClearInternalFlags(EInternalObjectFlags::Native);

	if (GShouldVerifyGCAssumptions && GUObjectArray.IsDisregardForGC(InClass))
	{
		NewFunction->AddToRoot();
	}

	return NewFunction;
}

void FCSharpBind::UpdateCallCSharpFunction(UFunction* InFunction)
{
	if (InFunction == nullptr)
	{
		return;
	}

	UpdateCallCSharpFunctionFlags(InFunction);

	if (!InFunction->HasAnyFunctionFlags(FUNC_Native) && !InFunction->Script.IsEmpty())
	{
		InFunction->Script.Empty(3 + sizeof(void*));
	}

	InFunction->SetNativeFunc((FNativeFuncPtr)(&FCSharpInvoker::execCallCSharp));

	if (InFunction->Script.Num() < 1)
	{
		InFunction->Script.Add(EX_CallCSharp);

		InFunction->Script.Add(EX_Return);

		InFunction->Script.Add(EX_Nothing);
	}
}

void FCSharpBind::UpdateCallCSharpFunctionFlags(UFunction* InFunctionCallLua)
{
	if (InFunctionCallLua == nullptr)
	{
		return;
	}

	if (InFunctionCallLua->GetReturnProperty())
	{
		InFunctionCallLua->FunctionFlags |= FUNC_HasOutParms;
	}

	InFunctionCallLua->FunctionFlags &= (~FUNC_Native);
}

bool FCSharpBind::IsOverrideType(const FDomain* InDomain, MonoReflectionType* InMonoReflectionType)
{
	if (InDomain == nullptr || InMonoReflectionType == nullptr)
	{
		return false;
	}

	if (const auto UtilsMonoClass = InDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS))
	{
		auto InParams = static_cast<void*>(InMonoReflectionType);

		if (const auto IsOverrideTypeMonoMethod = InDomain->Class_Get_Method_From_Name(
			UtilsMonoClass,FUNCTION_UTILS_IS_OVERRIDE_TYPE, TGetArrayLength(InParams)))
		{
			if (const auto IsOverrideTypeMonoObject = InDomain->Runtime_Invoke(
				IsOverrideTypeMonoMethod, nullptr, &InParams))
			{
				return *static_cast<bool*>(InDomain->Object_Unbox(IsOverrideTypeMonoObject));
			}
		}
	}

	return false;
}

bool FCSharpBind::IsOverrideMethod(const FDomain* InDomain, MonoReflectionMethod* InMonoReflectionMethod)
{
	if (InDomain == nullptr || InMonoReflectionMethod == nullptr)
	{
		return false;
	}

	if (const auto UtilsMonoClass = InDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS))
	{
		auto InParams = static_cast<void*>(InMonoReflectionMethod);

		if (const auto IsOverrideMethodMonoMethod = InDomain->Class_Get_Method_From_Name(
			UtilsMonoClass,FUNCTION_UTILS_IS_OVERRIDE_METHOD, TGetArrayLength(InParams)))
		{
			if (const auto IsOverrideMethodMonoObject = InDomain->Runtime_Invoke(
				IsOverrideMethodMonoMethod, nullptr, &InParams))
			{
				return *static_cast<bool*>(InDomain->Object_Unbox(IsOverrideMethodMonoObject));
			}
		}
	}

	return false;
}

void FCSharpBind::OnCSharpEnvironmentInitialize()
{
	for (const auto Class : TObjectRange<UClass>())
	{
		if (Class->ClassDefaultObject)
		{
			BindClassDefaultObject(FCSharpEnvironment::GetEnvironment().GetDomain(), Class->ClassDefaultObject);
		}
	}
}
