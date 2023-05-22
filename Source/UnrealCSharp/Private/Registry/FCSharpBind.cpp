#include "Registry/FCSharpBind.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FCSharpInvoker.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Template/TGetArrayLength.h"

#if !WITH_EDITOR
TSet<TWeakObjectPtr<UStruct>> FCSharpBind::NotOverrideTypes;
#endif

MonoObject* FCSharpBind::Bind(FDomain* InDomain, UObject* InObject)
{
	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
	{
		return FoundMonoObject;
	}

	return Bind(InDomain, InObject, false) ? FCSharpEnvironment::GetEnvironment().GetObject(InObject) : nullptr;
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

bool FCSharpBind::Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                       MonoReflectionType* InValueReflectionType)
{
	return BindImplementation(InMonoObject, InKeyReflectionType, InValueReflectionType);
}

bool FCSharpBind::Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	return BindImplementation(InDomain, InMonoObject, InStructName);
}

bool FCSharpBind::Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	return BindImplementation(InClassDescriptor, InClass, InFunction);
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

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment().NewClassDescriptor(InDomain, InStruct);

	if (NewClassDescriptor == nullptr)
	{
		return false;
	}

	for (TFieldIterator<FProperty> It(InStruct, EFieldIteratorFlags::ExcludeSuper,
	                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
	{
		if (const auto Property = *It)
		{
			if (!NewClassDescriptor->PropertyDescriptorMap.Contains(Property->GetFName()))
			{
				NewClassDescriptor->PropertyDescriptorMap.Add(Property->GetFName(),
				                                              FPropertyDescriptor::Factory(Property));
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

			for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::IncludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::IncludeInterfaces); It; ++It)
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
					FoundMonoClass, FunctionPair.Key.ToString(),
					FunctionPair.Value->ReturnValueOffset != MAX_uint16
						? (FunctionPair.Value->NumParms > 0
							   ? FunctionPair.Value->NumParms - 1
							   : 0)
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

	if (InClassDescriptor->FunctionDescriptorMap.Contains(InFunction->GetFName()))
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

		InClassDescriptor->FunctionDescriptorMap.Add(InFunction->GetFName(), NewFunctionDescriptor);

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

		InClassDescriptor->FunctionDescriptorMap.Add(InFunction->GetFName(), NewFunctionDescriptor);

		NewFunctionDescriptor->OriginalFunction = OriginalFunction;

		UpdateCallCSharpFunction(NewFunction);
	}

	return true;
}

bool FCSharpBind::BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                                     MonoReflectionType* InValueReflectionType)
{
	const auto KeyProperty = FTypeBridge::Factory(InKeyReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ValueProperty =
		FTypeBridge::Factory(InValueReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(MapHelper, InMonoObject);

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

	FCSharpEnvironment::GetEnvironment().AddStructReference(InScriptStruct, nullptr, Structure, InMonoObject);

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

	const auto FoundFunctionDescriptor = InClassDescriptor->GetFunctionDescriptor(InFunction->GetFName());

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

	FObjectDuplicationParameters ObjectDuplicationParameters(InOriginalFunction, InClass);

	ObjectDuplicationParameters.DestName = InFunctionName;

	ObjectDuplicationParameters.InternalFlagMask &= (~EInternalObjectFlags::Native);

	const auto NewFunction = Cast<UFunction>(StaticDuplicateObjectEx(ObjectDuplicationParameters));

	if (NewFunction == nullptr)
	{
		return nullptr;
	}

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

	if (!InFunction->HasAnyFunctionFlags(FUNC_Native) && InFunction->Script.Num() > 0)
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
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
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
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
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
