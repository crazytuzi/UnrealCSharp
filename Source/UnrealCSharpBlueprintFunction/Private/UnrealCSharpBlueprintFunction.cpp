#include "CSharpFunctionInjector.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include <atomic>

#include "Containers/Ticker.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Domain/Script/FScriptDomainScope.h"
#include "Engine/Blueprint.h"
#include "Misc/CoreDelegates.h"
#include "UObject/UObjectIterator.h"
#endif

class FUnrealCSharpBlueprintFunctionModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		OnCSharpClassBindingHandle = FUnrealCSharpModuleDelegates::GetOnCSharpClassBinding().AddLambda([](UClass* InClass)
		{
			FCSharpFunctionInjector::InjectClass(InClass);
		});

#if WITH_EDITOR
		OnPostEngineInitHandle = FCoreDelegates::GetOnPostEngineInit().AddRaw(
			this, &FUnrealCSharpBlueprintFunctionModule::InjectAllLoadedBlueprints);

		OnCompileHandle = FUnrealCSharpCoreModuleDelegates::OnCompile.AddRaw(
			this, &FUnrealCSharpBlueprintFunctionModule::OnCompile);

		OnAssetLoadedHandle = FCoreUObjectDelegates::OnAssetLoaded.AddRaw(
			this, &FUnrealCSharpBlueprintFunctionModule::OnAssetLoaded);
#endif
	}

	virtual void ShutdownModule() override
	{
		if (OnCSharpClassBindingHandle.IsValid())
		{
			FUnrealCSharpModuleDelegates::GetOnCSharpClassBinding().Remove(OnCSharpClassBindingHandle);
		}

#if WITH_EDITOR
		if (OnAssetLoadedHandle.IsValid())
		{
			FCoreUObjectDelegates::OnAssetLoaded.Remove(OnAssetLoadedHandle);
		}

		if (OnCompileHandle.IsValid())
		{
			FUnrealCSharpCoreModuleDelegates::OnCompile.Remove(OnCompileHandle);
		}

		if (OnPostEngineInitHandle.IsValid())
		{
			FCoreDelegates::GetOnPostEngineInit().Remove(OnPostEngineInitHandle);
		}

		for (const auto& HookedBlueprint : HookedBlueprints)
		{
			if (const auto Blueprint = HookedBlueprint.Get())
			{
				Blueprint->OnCompiled().RemoveAll(this);
			}
		}

		HookedBlueprints.Empty();
#endif
	}

private:
	FDelegateHandle OnCSharpClassBindingHandle;

#if WITH_EDITOR
	void InjectAllLoadedBlueprints()
	{
		FScriptDomainScope Scope([this]
		{
			FCSharpFunctionInjector::RebuildInjectableClassCache();

			for (TObjectIterator<UBlueprint> It; It; ++It)
			{
				if (FCSharpFunctionInjector::MayHaveInjectableFunctions(It->GeneratedClass))
				{
					InjectBlueprint(*It);
				}
			}
		});
	}

	// OnCompile 在编译器工作线程广播，创建脚本域/遍历 UObject 必须回游戏线程。
	void OnCompile(const bool bSucceeded)
	{
		if (bSucceeded)
		{
			bFullInjectionPending = true;

			ScheduleFlush();
		}
	}

	void OnAssetLoaded(UObject* InObject)
	{
		if (const auto Blueprint = Cast<UBlueprint>(InObject);
			Blueprint != nullptr && FCSharpFunctionInjector::MayHaveInjectableFunctions(Blueprint->GeneratedClass))
		{
			PendingBlueprints.Add(Blueprint);

			ScheduleFlush();
		}
	}

	// 编译完成必须同帧重注入：蓝图编辑器随后立即重建节点 UI，延迟一帧会让委托下拉/校验短暂丢失函数。
	void OnBlueprintCompiled(UBlueprint* InBlueprint)
	{
		if (FCSharpFunctionInjector::MayHaveInjectableFunctions(InBlueprint->GeneratedClass))
		{
			FScriptDomainScope Scope([this, InBlueprint]
			{
				InjectBlueprint(InBlueprint);
			});
		}
	}

	void InjectBlueprint(UBlueprint* InBlueprint)
	{
		if (FCSharpFunctionInjector::InjectBlueprint(InBlueprint))
		{
			if (!HookedBlueprints.Contains(InBlueprint))
			{
				HookedBlueprints.Add(InBlueprint);

				InBlueprint->OnCompiled().AddRaw(this, &FUnrealCSharpBlueprintFunctionModule::OnBlueprintCompiled);
			}
		}
	}

	void ScheduleFlush()
	{
		if (bFlushScheduled.exchange(true))
		{
			return;
		}

		if (IsRunningCommandlet() && IsInGameThread())
		{
			FlushPendingBlueprints();

			return;
		}

		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(
			this, &FUnrealCSharpBlueprintFunctionModule::OnFlushTick));
	}

	bool OnFlushTick(float)
	{
		FlushPendingBlueprints();

		return false;
	}

	void FlushPendingBlueprints()
	{
		bFlushScheduled = false;

		if (bFullInjectionPending.exchange(false))
		{
			PendingBlueprints.Empty();

			InjectAllLoadedBlueprints();

			return;
		}

		if (PendingBlueprints.IsEmpty())
		{
			return;
		}

		FScriptDomainScope Scope([this]
		{
			for (const auto& PendingBlueprint : PendingBlueprints)
			{
				if (const auto Blueprint = PendingBlueprint.Get())
				{
					InjectBlueprint(Blueprint);
				}
			}
		});

		PendingBlueprints.Empty();
	}

	std::atomic<bool> bFlushScheduled{};

	std::atomic<bool> bFullInjectionPending{};

	TSet<TWeakObjectPtr<UBlueprint>> PendingBlueprints;

	TSet<TWeakObjectPtr<UBlueprint>> HookedBlueprints;

	FDelegateHandle OnPostEngineInitHandle;

	FDelegateHandle OnCompileHandle;

	FDelegateHandle OnAssetLoadedHandle;
#endif
};

IMPLEMENT_MODULE(FUnrealCSharpBlueprintFunctionModule, UnrealCSharpBlueprintFunction)
