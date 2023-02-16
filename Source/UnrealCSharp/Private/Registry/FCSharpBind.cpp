#include "Registry/FCSharpBind.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FCSharpInvoker.h"
#include "FUnrealCSharpFunctionLibrary.h"

TSet<TWeakObjectPtr<UStruct>> FCSharpBind::NotOverrideTypes;

bool FCSharpBind::Bind(FMonoDomain* InMonoDomain, UObject* InObject)
{
	return BindImplementation(InMonoDomain, InObject);
}

bool FCSharpBind::Bind(FMonoDomain* InMonoDomain, UStruct* InStruct, const bool bNeedMonoClass)
{
	if (bNeedMonoClass && !CanBind(InMonoDomain, InStruct))
	{
		NotOverrideTypes.Add(InStruct);
		
		return false;
	}

	return BindImplementation(InMonoDomain, InStruct);
}

bool FCSharpBind::Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                       MonoReflectionType* InValueReflectionType)
{
	return BindImplementation(InMonoObject, InKeyReflectionType, InValueReflectionType);
}

bool FCSharpBind::Bind(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	return BindImplementation(InMonoDomain, InMonoObject, InStructName);
}

bool FCSharpBind::Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	return BindImplementation(InClassDescriptor, InClass, InFunction);
}

bool FCSharpBind::BindImplementation(FMonoDomain* InMonoDomain, UObject* InObject)
{
	if (InMonoDomain == nullptr || InObject == nullptr)
	{
		return false;
	}

	const auto InClass = InObject->GetClass();

	if (InClass == nullptr)
	{
		return false;
	}

	if (!Bind(InMonoDomain, InClass))
	{
		return false;
	}

	const auto FoundClassDescriptor = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(InClass);

	if (FoundClassDescriptor == nullptr)
	{
		return false;
	}

	const auto FoundMonoClass = FoundClassDescriptor->GetMonoClass();

	if (FoundMonoClass == nullptr)
	{
		return false;
	}

	const auto NewMonoObject = InMonoDomain->Object_New(FoundMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddObjectReference(InObject, NewMonoObject);

	return true;
}

bool FCSharpBind::BindImplementation(FMonoDomain* InMonoDomain, UStruct* InStruct)
{
	if (InMonoDomain == nullptr || InStruct == nullptr)
	{
		return false;
	}

	auto SuperStruct = InStruct->GetSuperStruct();

	while (SuperStruct != nullptr)
	{
		Bind(InMonoDomain, SuperStruct, false);

		SuperStruct = SuperStruct->GetSuperStruct();
	}

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment()->NewClassDescriptor(InMonoDomain, InStruct);

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
		if (const auto FoundMonoClass = InMonoDomain->Class_From_Name(
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
				if (const auto FoundMonoMethod = InMonoDomain->Class_Get_Method_From_Name(FoundMonoClass, FunctionPair.Key.ToString(),
				                                             FunctionPair.Value->ReturnValueOffset != MAX_uint16
					                                             ? (FunctionPair.Value->NumParms > 0
						                                                ? FunctionPair.Value->NumParms - 1
						                                                : 0)
					                                             : FunctionPair.Value->NumParms))
				{
					if (IsOverrideMethod(InMonoDomain,
					                     InMonoDomain->Method_Get_Object(FoundMonoMethod, FoundMonoClass)))
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
	const auto KeyProperty = FContainerHelper::Factory(InKeyReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	KeyProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto ValueProperty =
		FContainerHelper::Factory(InValueReflectionType, nullptr, "", EObjectFlags::RF_Transient);

	ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

	const auto MapHelper = new FMapHelper(KeyProperty, ValueProperty);

	FCSharpEnvironment::GetEnvironment()->AddContainerReference(MapHelper, InMonoObject);

	return true;
}

bool FCSharpBind::BindImplementation(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName)
{
	const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *InStructName.ToString());

	if (InMonoDomain == nullptr || InScriptStruct == nullptr)
	{
		return false;
	}

	if (!Bind(InMonoDomain, InScriptStruct, false))
	{
		return false;
	}

	const auto StructureSize = InScriptStruct->GetStructureSize() ? InScriptStruct->GetStructureSize() : 1;

	const auto Structure = static_cast<void*>(static_cast<uint8*>(FMemory::Malloc(StructureSize)));

	InScriptStruct->InitializeStruct(Structure);

	FCSharpEnvironment::GetEnvironment()->AddStructReference(InScriptStruct, Structure, InMonoObject);

	return true;
}

bool FCSharpBind::CanBind(const FMonoDomain* InMonoDomain, UStruct* InStruct)
{
	if (NotOverrideTypes.Contains(InStruct))
	{
		return false;
	}
	
	if (FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(InStruct))
	{
		return true;
	}

	if (const auto FoundMonoClass = InMonoDomain->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct),
		FUnrealCSharpFunctionLibrary::GetFullClass(InStruct)))
	{
		if (const auto FoundMonoType = InMonoDomain->Class_Get_Type(FoundMonoClass))
		{
			if (const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundMonoType))
			{
				return IsOverrideType(InMonoDomain, FoundReflectionType);
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

bool FCSharpBind::IsOverrideType(const FMonoDomain* InMonoDomain, MonoReflectionType* InMonoReflectionType)
{
	if (InMonoDomain == nullptr || InMonoReflectionType == nullptr)
	{
		return false;
	}

	if (const auto UtilsMonoClass = InMonoDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
	{
		if (const auto IsOverrideTypeMonoMethod = InMonoDomain->Class_Get_Method_From_Name(
			UtilsMonoClass,FUNCTION_UTILS_IS_OVERRIDE_TYPE, 1))
		{
			auto InParams = static_cast<void*>(InMonoReflectionType);

			if (const auto IsOverrideTypeMonoObject = InMonoDomain->Runtime_Invoke(
				IsOverrideTypeMonoMethod, nullptr, &InParams, nullptr))
			{
				return *static_cast<bool*>(InMonoDomain->Object_Unbox(IsOverrideTypeMonoObject));
			}
		}
	}

	return false;
}

bool FCSharpBind::IsOverrideMethod(const FMonoDomain* InMonoDomain, MonoReflectionMethod* InMonoReflectionMethod)
{
	if (InMonoDomain == nullptr || InMonoReflectionMethod == nullptr)
	{
		return false;
	}

	if (const auto UtilsMonoClass = InMonoDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
	{
		if (const auto IsOverrideMethodMonoMethod = InMonoDomain->Class_Get_Method_From_Name(
			UtilsMonoClass,FUNCTION_UTILS_IS_OVERRIDE_METHOD, 1))
		{
			auto InParams = static_cast<void*>(InMonoReflectionMethod);

			if (const auto IsOverrideMethodMonoObject = InMonoDomain->Runtime_Invoke(
				IsOverrideMethodMonoMethod, nullptr, &InParams, nullptr))
			{
				return *static_cast<bool*>(InMonoDomain->Object_Unbox(IsOverrideMethodMonoObject));
			}
		}
	}

	return false;
}
