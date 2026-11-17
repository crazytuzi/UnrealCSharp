#include "CSharpBlueprintFunctionLibrary.h"

#include "CSharpBlueprintCallDescriptor.h"
#include "CSharpBlueprintMember.h"
#include "CSharpDelegateProxy.h"
#include "Log/UnrealCSharpLog.h"

static void LogOnce(const UObject* InTarget, const FName& InMemberName, const TCHAR* InMessage)
{
	static TSet<uint32> Logged;

	const auto Key = HashCombine(GetTypeHash(InTarget != nullptr ? InTarget->GetClass()->GetFName() : NAME_None),
	                             HashCombine(GetTypeHash(InMemberName), GetTypeHash(FString(InMessage))));

	if (!Logged.Contains(Key))
	{
		Logged.Add(Key);

		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpBlueprintCall: %s.%s %s"),
		       InTarget != nullptr ? *InTarget->GetClass()->GetName() : TEXT("None"), *InMemberName.ToString(),
		       InMessage);
	}
}

static void ExecCSharpMember(FFrame& Stack, const ECSharpBlueprintMemberKind InKind)
{
	P_GET_OBJECT(UObject, Target);
	P_GET_PROPERTY(FNameProperty, MemberName);
	P_GET_PROPERTY(FIntProperty, ParamCount);
	P_GET_PROPERTY(FIntProperty, SignatureHash);

	P_NATIVE_BEGIN;

	FCSharpBlueprintCallDescriptor* Descriptor = nullptr;

	if (Target == nullptr)
	{
		LogOnce(nullptr, MemberName, TEXT("Target is null"));
	}
	else if (!FCSharpBlueprintMemberLibrary::IsRuntimeActive())
	{
		LogOnce(Target, MemberName, TEXT("C# runtime is not active, call skipped"));
	}
	else
	{
		Descriptor = FCSharpBlueprintCallCache::Get().Resolve(Target->GetClass(), InKind, MemberName, ParamCount);

		if (Descriptor != nullptr && Descriptor->GetSignatureHash() != static_cast<uint32>(SignatureHash))
		{
			LogOnce(Target, MemberName, TEXT("C# signature changed since the Blueprint was compiled, recompile the Blueprint"));

			Descriptor = nullptr;
		}
	}

	if (Descriptor != nullptr)
	{
		Descriptor->Call(Target, Stack);
	}
	else
	{
		FCSharpBlueprintCallDescriptor::SkipParams(Stack);
	}

	P_NATIVE_END;

	P_FINISH;
}

void UCSharpBlueprintFunctionLibrary::CallCSharpFunction(UObject*, FName, int32, int32)
{
	checkNoEntry();
}

void UCSharpBlueprintFunctionLibrary::GetCSharpProperty(UObject*, FName, int32, int32)
{
	checkNoEntry();
}

void UCSharpBlueprintFunctionLibrary::SetCSharpProperty(UObject*, FName, int32, int32)
{
	checkNoEntry();
}

DEFINE_FUNCTION(UCSharpBlueprintFunctionLibrary::execCallCSharpFunction)
{
	ExecCSharpMember(Stack, ECSharpBlueprintMemberKind::Function);
}

DEFINE_FUNCTION(UCSharpBlueprintFunctionLibrary::execGetCSharpProperty)
{
	ExecCSharpMember(Stack, ECSharpBlueprintMemberKind::PropertyGet);
}

DEFINE_FUNCTION(UCSharpBlueprintFunctionLibrary::execSetCSharpProperty)
{
	ExecCSharpMember(Stack, ECSharpBlueprintMemberKind::PropertySet);
}

UObject* UCSharpBlueprintFunctionLibrary::GetCSharpDelegateProxy(UObject* Target, const FName FunctionName,
                                                                 const int32 ParamCount, const int32 SignatureHash)
{
	if (Target == nullptr)
	{
		LogOnce(nullptr, FunctionName, TEXT("Target is null, cannot create delegate"));

		return nullptr;
	}

	return UCSharpDelegateProxy::GetOrCreate(Target, ECSharpBlueprintMemberKind::Function, FunctionName, ParamCount,
	                                         static_cast<uint32>(SignatureHash));
}

UFunction* UCSharpBlueprintFunctionLibrary::GetCallFunction()
{
	return StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UCSharpBlueprintFunctionLibrary, CallCSharpFunction));
}

UFunction* UCSharpBlueprintFunctionLibrary::GetGetPropertyFunction()
{
	return StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UCSharpBlueprintFunctionLibrary, GetCSharpProperty));
}

UFunction* UCSharpBlueprintFunctionLibrary::GetSetPropertyFunction()
{
	return StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(UCSharpBlueprintFunctionLibrary, SetCSharpProperty));
}

UFunction* UCSharpBlueprintFunctionLibrary::GetDelegateProxyFunction()
{
	return StaticClass()->FindFunctionByName(
		GET_FUNCTION_NAME_CHECKED(UCSharpBlueprintFunctionLibrary, GetCSharpDelegateProxy));
}
