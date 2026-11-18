#include "CSharpDelegateProxy.h"

#include "CSharpBlueprintCallDescriptor.h"
#include "CSharpBlueprintMember.h"
#include "Log/UnrealCSharpLog.h"
#include "UObject/Package.h"
#include "UObject/StrongObjectPtr.h"
#include "UObject/UObjectGlobals.h"

namespace
{
	struct FProxyKey
	{
		TWeakObjectPtr<UObject> Target;

		ECSharpBlueprintMemberKind Kind;

		FName MemberName;

		int32 ParamCount;

		bool operator==(const FProxyKey& InOther) const
		{
			return Target == InOther.Target && Kind == InOther.Kind && MemberName == InOther.MemberName &&
				ParamCount == InOther.ParamCount;
		}

		friend uint32 GetTypeHash(const FProxyKey& InKey)
		{
			return HashCombine(HashCombine(GetTypeHash(InKey.Target), GetTypeHash(InKey.MemberName)),
			                   HashCombine(static_cast<uint32>(InKey.Kind), static_cast<uint32>(InKey.ParamCount)));
		}
	};

	class FProxyRegistry
	{
	public:
		static FProxyRegistry& Get()
		{
			static FProxyRegistry Registry;

			return Registry;
		}

		UCSharpDelegateProxy* GetOrCreate(UObject* InTarget, const ECSharpBlueprintMemberKind InKind,
		                                  const FName& InMemberName, const int32 InParamCount,
		                                  const uint32 InSignatureHash)
		{
			EnsureHooked();

			const FProxyKey Key{InTarget, InKind, InMemberName, InParamCount};

			if (const auto Found = Proxies.Find(Key))
			{
				if (const auto Proxy = Found->Get(); Proxy != nullptr && Proxy->Target.IsValid())
				{
					Proxy->SignatureHash = InSignatureHash;

					return Proxy;
				}

				Proxies.Remove(Key);
			}

			const auto Proxy = NewObject<UCSharpDelegateProxy>(GetTransientPackage(), NAME_None, RF_Transient);

			Proxy->Target = InTarget;

			Proxy->Kind = InKind;

			Proxy->MemberName = InMemberName;

			Proxy->ParamCount = InParamCount;

			Proxy->SignatureHash = InSignatureHash;

			Proxies.Add(Key, TStrongObjectPtr<UCSharpDelegateProxy>(Proxy));

			return Proxy;
		}

		void Reset()
		{
			Proxies.Empty();

			if (PostGarbageCollectHandle.IsValid())
			{
				FCoreUObjectDelegates::GetPostGarbageCollect().Remove(PostGarbageCollectHandle);

				PostGarbageCollectHandle.Reset();
			}

			if (PreExitHandle.IsValid())
			{
				FCoreDelegates::OnPreExit.Remove(PreExitHandle);

				PreExitHandle.Reset();
			}
		}

	private:
		void EnsureHooked()
		{
			if (!PostGarbageCollectHandle.IsValid())
			{
				PostGarbageCollectHandle = FCoreUObjectDelegates::GetPostGarbageCollect().AddRaw(
					this, &FProxyRegistry::Prune);
			}

			if (!PreExitHandle.IsValid())
			{
				PreExitHandle = FCoreDelegates::OnPreExit.AddRaw(this, &FProxyRegistry::Reset);
			}
		}

		void Prune()
		{
			for (auto It = Proxies.CreateIterator(); It; ++It)
			{
				if (!It.Key().Target.IsValid() || !It.Value().IsValid())
				{
					It.RemoveCurrent();
				}
			}
		}

		TMap<FProxyKey, TStrongObjectPtr<UCSharpDelegateProxy>> Proxies;

		FDelegateHandle PostGarbageCollectHandle;

		FDelegateHandle PreExitHandle;
	};
}

void UCSharpDelegateProxy::Invoke()
{
}

void UCSharpDelegateProxy::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function == nullptr || Function->GetFName() != GetInvokeFunctionName())
	{
		Super::ProcessEvent(Function, Parms);

		return;
	}

	const auto FoundTarget = Target.Get();

	if (FoundTarget == nullptr)
	{
		return;
	}

	if (!FCSharpBlueprintMemberLibrary::IsRuntimeActive())
	{
		UE_LOG(LogUnrealCSharp, Warning, TEXT("CSharpDelegateProxy: C# runtime is not active, skipped %s.%s"),
		       *FoundTarget->GetClass()->GetName(), *MemberName.ToString());

		return;
	}

	const auto Descriptor = FCSharpBlueprintCallCache::Get().Resolve(FoundTarget->GetClass(), Kind, MemberName,
	                                                                 ParamCount);

	if (Descriptor == nullptr)
	{
		return;
	}

	if (Descriptor->GetSignatureHash() != SignatureHash)
	{
		UE_LOG(LogUnrealCSharp, Error,
		       TEXT("CSharpDelegateProxy: delegate signature of %s.%s does not match the current C# signature, recompile the Blueprint"),
		       *FoundTarget->GetClass()->GetName(), *MemberName.ToString());

		return;
	}

	Descriptor->CallWithParams(FoundTarget, Parms);
}

FName UCSharpDelegateProxy::GetInvokeFunctionName()
{
	static const FName Name(GET_FUNCTION_NAME_CHECKED(UCSharpDelegateProxy, Invoke));

	return Name;
}

UCSharpDelegateProxy* UCSharpDelegateProxy::GetOrCreate(UObject* InTarget, const ECSharpBlueprintMemberKind InKind,
                                                        const FName& InMemberName, const int32 InParamCount,
                                                        const uint32 InSignatureHash)
{
	if (InTarget == nullptr)
	{
		return nullptr;
	}

	return FProxyRegistry::Get().GetOrCreate(InTarget, InKind, InMemberName, InParamCount, InSignatureHash);
}

void UCSharpDelegateProxy::ResetRegistry()
{
	FProxyRegistry::Get().Reset();
}
