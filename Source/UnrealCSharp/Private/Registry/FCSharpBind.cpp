#include "Registry/FCSharpBind.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/FCSharpInvoker.h"

bool FCSharpBind::Bind(FMonoDomain* InMonoDomain, UObject* InObject)
{
	return BindImplementation(InMonoDomain, InObject);
}

bool FCSharpBind::Bind(FMonoDomain* InMonoDomain, UClass* InClass, const bool bNeedMonoClass)
{
	if (bNeedMonoClass && !CanBind(InMonoDomain, InClass))
	{
		return false;
	}

	return BindImplementation(InMonoDomain, InClass);
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

	FCSharpEnvironment::GetEnvironment()->AddReference(InObject, NewMonoObject);

	return true;
}

bool FCSharpBind::BindImplementation(FMonoDomain* InMonoDomain, UClass* InClass)
{
	if (InMonoDomain == nullptr || InClass == nullptr)
	{
		return false;
	}

	auto SuperClass = InClass->GetSuperClass();

	while (SuperClass != nullptr)
	{
		Bind(InMonoDomain, SuperClass, false);

		SuperClass = SuperClass->GetSuperClass();
	}

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment()->NewClassDescriptor(InMonoDomain, InClass);

	if (NewClassDescriptor == nullptr)
	{
		return false;
	}

	if (const auto FoundMonoClass = InMonoDomain->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME), InClass->GetPrefixCPP() + InClass->GetName()))
	{
		InClass->ClearFunctionMapsCaches();

		TMap<FName, UFunction*> Functions;

		for (TFieldIterator<UFunction> It(InClass, EFieldIteratorFlags::IncludeSuper,
		                                  EFieldIteratorFlags::ExcludeDeprecated,
		                                  EFieldIteratorFlags::IncludeInterfaces); It; ++It)
		{
			if (auto Function = *It)
			{
				if (Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) && !Function->HasAnyFunctionFlags(FUNC_Final) &&
					!Functions.Contains(Function->GetFName()))
				{
					Functions.Emplace(Function->GetName(), Function);
				}
			}
		}

		for (const auto& FunctionPair : Functions)
		{
			if (InMonoDomain->Class_Get_Method_From_Name(FoundMonoClass, FunctionPair.Key.ToString(),
			                                             FunctionPair.Value->ReturnValueOffset != MAX_uint16
				                                             ? (FunctionPair.Value->NumParms > 0
					                                                ? FunctionPair.Value->NumParms - 1
					                                                : 0)
				                                             : FunctionPair.Value->NumParms))
			{
				Bind(NewClassDescriptor, InClass, FunctionPair.Value);
			}
		}
	}

	for (TFieldIterator<FProperty> It(InClass, EFieldIteratorFlags::ExcludeSuper,
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

	const auto OriginalFunction = GetOriginalFunction(InClassDescriptor, InClass, InFunction);

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

bool FCSharpBind::CanBind(const FMonoDomain* InMonoDomain, const UClass* InClass)
{
	if (FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(InClass))
	{
		return true;
	}

	return InMonoDomain->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME),
			InClass->GetPrefixCPP() + InClass->GetName()) != nullptr ||
		InMonoDomain->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE),
			InClass->GetPrefixCPP() + InClass->GetName()) != nullptr;
}

UFunction* FCSharpBind::GetOriginalFunction(FClassDescriptor* InClassDescriptor, const UClass* InClass,
                                            UFunction* InFunction)
{
	if (InClassDescriptor == nullptr || InClass == nullptr || InFunction == nullptr)
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

	return GetOriginalFunction(InClassDescriptor, SuperClass, SuperOriginalFunction);
}

bool FCSharpBind::IsCallCSharpFunction(UFunction* InFunction)
{
	return InFunction && (InFunction->GetNativeFunc() == &FCSharpInvoker::execCallCSharp) && (InFunction->Script.Num() >
		0) && (InFunction->Script[0] == EX_CallCSharp);
}

UFunction* FCSharpBind::DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName)
{
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
