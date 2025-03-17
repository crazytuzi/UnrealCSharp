#include "Registry/FCSharpBind.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/GenericAttributeMacro.h"
#include "Macro/FunctionMacro.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/CSharpFunction.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Template/TGetArrayLength.inl"
#include "Setting/UnrealCSharpSetting.h"
#include "UEVersion.h"

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

	return Bind<false>(InDomain, InObject);
}

MonoObject* FCSharpBind::Bind(FDomain* InDomain, UClass* InClass)
{
	Bind<false>(InDomain, InClass);

	return Bind(InDomain, static_cast<UObject*>(InClass));
}

bool FCSharpBind::Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	return BindImplementation(InDomain, InMonoObject, InStructName);
}

bool FCSharpBind::Bind(FDomain* InDomain, FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	return InFunction != nullptr
		       ? Bind(InDomain, InClassDescriptor, InClass, InFunction->GetName(), InFunction)
		       : false;
}

bool FCSharpBind::Bind(FDomain* InDomain, FClassDescriptor* InClassDescriptor, UClass* InClass,
                       const FString& InMethodName, UFunction* InFunction)
{
	return BindImplementation(InDomain, InClassDescriptor, InClass, InMethodName, InFunction);
}

bool FCSharpBind::BindClassDefaultObject(FDomain* InDomain, UObject* InObject)
{
	if (CanBind(InDomain, InObject->GetClass()))
	{
		FClassRegistry::AddClassConstructor(InObject->GetClass());

		Bind<false>(InDomain, InObject);

		return true;
	}
	else
	{
		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
			for (const auto& [Class, bNeedMonoClass] : UnrealCSharpSetting->GetBindClass())
			{
				if (InObject->IsA(Class))
				{
					return bNeedMonoClass ? false : !!Bind<false>(InDomain, InObject);
				}
			}
		}
	}

	return false;
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
		Bind<false>(InDomain, SuperStruct);

		SuperStruct = SuperStruct->GetSuperStruct();
	}

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment().AddClassDescriptor(InStruct);

	if (NewClassDescriptor == nullptr)
	{
		return false;
	}

	TMap<FString, MonoClassField*> Fields;

	void* FieldIterator = nullptr;

	while (const auto Field = FDomain::Class_Get_Fields(NewClassDescriptor->GetMonoClass(), &FieldIterator))
	{
		if (auto FieldName = FString(FDomain::Field_Get_Name(Field)); FieldName.StartsWith(TEXT("__")))
		{
			FieldName.RightChopInline(2);

			Fields.Add(FieldName, Field);
		}
	}

	TMap<FString, FProperty*> Properties;

	for (TFieldIterator<FProperty> It(InStruct, EFieldIteratorFlags::ExcludeSuper,
	                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
	{
		if (const auto Property = *It)
		{
			Properties.Add(FUnrealCSharpFunctionLibrary::Encode(Property), Property);
		}
	}

	for (const auto& [PropertyName, Property] : Properties)
	{
		for (const auto& [FieldName, Field] : Fields)
		{
			if (FieldName == PropertyName)
			{
				auto FieldHash = GetTypeHash(Property);

				InDomain->Field_Static_Set_Value(InDomain->Class_VTable(NewClassDescriptor->GetMonoClass()),
				                                 Field, &FieldHash);

				FCSharpEnvironment::GetEnvironment().AddPropertyHash(FieldHash, NewClassDescriptor, FieldName);

				Fields.Remove(FieldName);

				break;
			}
		}
	}

	if (const auto InClass = Cast<UClass>(InStruct))
	{
		if (const auto FoundMonoClass = InDomain->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InClass)))
		{
			TMap<FString, UFunction*> Functions;

			for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
			{
				if (const auto Function = *It)
				{
					Functions.Add(FUnrealCSharpFunctionLibrary::Encode(Function), Function);
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
						Functions.Add(FUnrealCSharpFunctionLibrary::Encode(Function), Function);
					}
				}
			}

			for (const auto& [FunctionName, Function] : Functions)
			{
				for (const auto& [FieldName, Field] : Fields)
				{
					if (FieldName == FunctionName)
					{
						auto FieldHash = GetTypeHash(Function);

						InDomain->Field_Static_Set_Value(InDomain->Class_VTable(NewClassDescriptor->GetMonoClass()),
						                                 Field, &FieldHash);

						FCSharpEnvironment::GetEnvironment().AddFunctionHash(FieldHash, NewClassDescriptor, FieldName);

						Fields.Remove(FieldName);

						break;
					}
				}
			}

			Functions.Empty();

			for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::IncludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
			{
				if (auto Function = *It)
				{
					if (Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) &&
#if UE_DO_NATIVE_IMPL_OPTIMIZATION
						!Function->HasAnyFunctionFlags(FUNC_Native) &&
#endif
						!Function->HasAnyFunctionFlags(FUNC_Final))
					{
						if (const auto Name = Function->GetName(); !Functions.Contains(Name))
						{
							Functions.Emplace(FUnrealCSharpFunctionLibrary::Encode(
								                  Function->HasAnyFunctionFlags(FUNC_Net)
									                  ? FString::Printf(TEXT(
										                  "%s_Implementation"
									                  ),
									                                    *Name
									                  )
									                  : Name,
								                  Function->IsNative()),
							                  Function);
						}
					}
				}
			}

			TMap<FString, MonoMethod*> Methods;

			const auto AttributeMonoClass = FDomain::Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_OVERRIDE_ATTRIBUTE);

			void* MethodIterator = nullptr;

			while (const auto Method = FDomain::Class_Get_Methods(FoundMonoClass, &MethodIterator))
			{
				if (const auto Attrs = FDomain::Custom_Attrs_From_Method(Method))
				{
					if (!!FDomain::Custom_Attrs_Has_Attr(Attrs, AttributeMonoClass))
					{
						const auto MethodName = FString(FDomain::Method_Get_Name(Method));

						Methods.Add(MethodName, Method);
					}
				}
			}

			for (const auto& [FunctionName, Function] : Functions)
			{
				for (const auto& [MethodName, Method] : Methods)
				{
					if (FunctionName == MethodName)
					{
						const auto Signature = FDomain::Method_Signature(Method);

						const auto MethodParamCount = FDomain::Signature_Get_Param_Count(Signature);

						auto FunctionParamCount = Function->ReturnValueOffset != MAX_uint16
							                          ? Function->NumParms - 1
							                          : Function->NumParms;

						if (MethodParamCount == FunctionParamCount)
						{
							Bind(InDomain, NewClassDescriptor, InClass, MethodName, Function);

							Methods.Remove(MethodName);

							break;
						}
					}
				}
			}
		}
	}

	return true;
}

bool FCSharpBind::BindImplementation(FDomain* InDomain, FClassDescriptor* InClassDescriptor,
                                     UClass* InClass, const FString& InMethodName, UFunction* InFunction)
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
		const auto NewFunctionDescriptor = new FCSharpFunctionDescriptor(InMethodName, OriginalFunction);

		const auto FunctionHash = GetTypeHash(NewFunctionDescriptor);

		InClassDescriptor->FunctionHashSet.Add(FunctionHash);

		FCSharpEnvironment::GetEnvironment().AddFunctionDescriptor(FunctionHash, NewFunctionDescriptor);

		const auto& NewFunctionName = FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(FunctionName);

		NewFunctionDescriptor->OriginalFunctionFlags = OriginalFunction->FunctionFlags;

		NewFunctionDescriptor->OriginalNativeFuncPtr = OriginalFunction->GetNativeFunc();

		const auto OverrideFunction = DuplicateFunction(OriginalFunction, InClass, *NewFunctionName);

		if (FUnrealCSharpFunctionLibrary::EnableCallOverrideFunction())
		{
			const auto& OverrideMethodName = FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(InMethodName);

			const auto OverrideFunctionDescriptor = new FCSharpFunctionDescriptor(
				OverrideMethodName, OverrideFunction);

			auto OverrideFunctionHash = GetTypeHash(OverrideFunction);

			InClassDescriptor->FunctionHashSet.Add(OverrideFunctionHash);

			FCSharpEnvironment::GetEnvironment().
				AddFunctionDescriptor(OverrideFunctionHash, OverrideFunctionDescriptor);

			if (const auto FoundField = InDomain->Self_Class_Get_Field_From_Name(
				InClassDescriptor->GetMonoClass(), TCHAR_TO_UTF8(*FString::Printf(TEXT(
						"__%s"
					),
					*OverrideMethodName
				))))
			{
				InDomain->Field_Static_Set_Value(InDomain->Class_VTable(InClassDescriptor->GetMonoClass()),
				                                 FoundField, &OverrideFunctionHash);
			}

			FCSharpEnvironment::GetEnvironment().AddFunctionHash(
				OverrideFunctionHash, InClassDescriptor, OverrideMethodName);
		}

		NewFunctionDescriptor->OriginalFunction = OverrideFunction;

		OriginalFunction->SetNativeFunc(UCSharpFunction::execCallCSharp);

		OriginalFunction->FunctionFlags |= FUNC_Native;
	}
	else
	{
		auto NewFunction = InClass->FindFunctionByName(FunctionName, EIncludeSuperFlag::ExcludeSuper);

		if (NewFunction != nullptr)
		{
			return false;
		}

		NewFunction = DuplicateFunction(OriginalFunction, InClass, FunctionName);

		const auto NewFunctionDescriptor = new FCSharpFunctionDescriptor(InMethodName, NewFunction);

		const auto FunctionHash = GetTypeHash(NewFunctionDescriptor);

		InClassDescriptor->FunctionHashSet.Add(FunctionHash);

		FCSharpEnvironment::GetEnvironment().AddFunctionDescriptor(FunctionHash, NewFunctionDescriptor);

		NewFunctionDescriptor->OriginalFunction = OriginalFunction;

		NewFunction->SetNativeFunc(UCSharpFunction::execCallCSharp);

		NewFunction->FunctionFlags |= FUNC_Native;
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

	if (!Bind<false>(InDomain, InScriptStruct))
	{
		return false;
	}

	const auto StructureSize = InScriptStruct->GetStructureSize() ? InScriptStruct->GetStructureSize() : 1;

	const auto Structure = static_cast<void*>(static_cast<uint8*>(FMemory::Malloc(StructureSize)));

	InScriptStruct->InitializeStruct(Structure);

	FCSharpEnvironment::GetEnvironment().AddStructReference<true>(InScriptStruct, Structure, InMonoObject);

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

	MonoClass* FoundMonoClass{};

	if (const auto InClass = Cast<UClass>(InStruct))
	{
		FoundMonoClass = InDomain->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InClass));
	}
	else if (const auto InScriptStruct = Cast<UScriptStruct>(InStruct))
	{
		FoundMonoClass = InDomain->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InScriptStruct),
			FUnrealCSharpFunctionLibrary::GetFullClass(InScriptStruct));
	}

	if (FoundMonoClass != nullptr)
	{
		if (const auto FoundMonoType = InDomain->Class_Get_Type(FoundMonoClass))
		{
			if (const auto FoundReflectionType = InDomain->Type_Get_Object(FoundMonoType))
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

	const auto FoundFunctionDescriptor = static_cast<FCSharpFunctionDescriptor*>(
		InClassDescriptor->GetOrAddFunctionDescriptor(InFunction->GetName()));

	if (const auto OriginalFunction = FoundFunctionDescriptor != nullptr
		                                  ? FoundFunctionDescriptor->OriginalFunction.Get()
		                                  : nullptr;
		OriginalFunction != nullptr && !IsCallCSharpFunction(OriginalFunction))
	{
		return OriginalFunction;
	}

	const auto SuperClass = InFunction->GetOuterUClass()->GetSuperClass();

	const auto SuperOriginalFunction = SuperClass != nullptr
		                                   ? SuperClass->FindFunctionByName(InFunction->GetFName())
		                                   : nullptr;

	return GetOriginalFunction(InClassDescriptor, SuperOriginalFunction);
}

bool FCSharpBind::IsCallCSharpFunction(const UFunction* InFunction)
{
	return InFunction != nullptr && InFunction->GetNativeFunc() == &UCSharpFunction::execCallCSharp;
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

	ObjectDuplicationParameters.DestClass = UCSharpFunction::StaticClass();

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

	if (InClass->HasAnyInternalFlags(EInternalObjectFlags::RootSet) || GUObjectArray.IsDisregardForGC(InClass))
	{
		NewFunction->AddToRoot();
	}

	return NewFunction;
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
			UtilsMonoClass, FUNCTION_UTILS_IS_OVERRIDE_TYPE, TGetArrayLength(InParams)))
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
