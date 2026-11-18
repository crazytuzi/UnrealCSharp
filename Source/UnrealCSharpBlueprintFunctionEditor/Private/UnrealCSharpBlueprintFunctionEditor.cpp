#include "Modules/ModuleManager.h"

#include "BlueprintActionDatabase.h"
#include "Containers/Ticker.h"
#include "CSharpBlueprintMember.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Editor.h"
#include "Engine/Blueprint.h"
#include "K2Node_CallCSharpFunction.h"
#include "K2Node_CreateCSharpDelegate.h"
#include "K2Node_CSharpPropertyAccess.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Reflection/FClassReflection.h"
#include "UnrealCSharpCore.h"
#include "UObject/UObjectIterator.h"

class FUnrealCSharpBlueprintFunctionEditorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		if (IsRunningCommandlet())
		{
			return;
		}

		OnCompileHandle = FUnrealCSharpCoreModuleDelegates::OnCompile.AddRaw(
			this, &FUnrealCSharpBlueprintFunctionEditorModule::OnCompile);

		OnCoreModuleActiveHandle = FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.AddRaw(
			this, &FUnrealCSharpBlueprintFunctionEditorModule::ScheduleRefresh);

		OnAssetLoadedHandle = FCoreUObjectDelegates::OnAssetLoaded.AddRaw(
			this, &FUnrealCSharpBlueprintFunctionEditorModule::OnAssetLoaded);
	}

	virtual void ShutdownModule() override
	{
		if (OnAssetLoadedHandle.IsValid())
		{
			FCoreUObjectDelegates::OnAssetLoaded.Remove(OnAssetLoadedHandle);
		}

		if (OnCoreModuleActiveHandle.IsValid())
		{
			FUnrealCSharpCoreModuleDelegates::OnUnrealCSharpCoreModuleActive.Remove(OnCoreModuleActiveHandle);
		}

		if (OnCompileHandle.IsValid())
		{
			FUnrealCSharpCoreModuleDelegates::OnCompile.Remove(OnCompileHandle);
		}

		if (TickerHandle.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
		}
	}

private:
	void OnCompile(const bool bSucceeded)
	{
		if (bSucceeded)
		{
			ScheduleRefresh();
		}
	}

	void OnAssetLoaded(UObject* InObject)
	{
		if (const auto Blueprint = Cast<UBlueprint>(InObject);
			Blueprint != nullptr && Blueprint->GeneratedClass != nullptr &&
			OverrideClassNames.Contains(Blueprint->GeneratedClass->GetFName()))
		{
			ScheduleRefresh();
		}
	}

	void ScheduleRefresh()
	{
		if (TickerHandle.IsValid())
		{
			return;
		}

		TickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](float)
		{
			TickerHandle.Reset();

			Refresh();

			return false;
		}));
	}

	void Refresh()
	{
		if (GEditor == nullptr)
		{
			return;
		}

		if (auto& CoreModule = FUnrealCSharpCoreModule::Get(); CoreModule.IsOutdated() && !GIsPlayInEditorWorld)
		{
			CoreModule.Deactivate();

			CoreModule.Activate();
		}

		RebuildOverrideClassNames();

		if (FBlueprintActionDatabase* ActionDatabase = FBlueprintActionDatabase::TryGet())
		{
			ActionDatabase->RefreshClassActions(UK2Node_CallCSharpFunction::StaticClass());

			ActionDatabase->RefreshClassActions(UK2Node_CSharpPropertyAccess::StaticClass());

			ActionDatabase->RefreshClassActions(UK2Node_CreateCSharpDelegate::StaticClass());
		}

		RefreshLiveNodes();
	}

	void RebuildOverrideClassNames()
	{
		OverrideClassNames.Reset();

		UK2Node_CSharpMemberBase::WithScriptDomain([this]
		{
			FCSharpBlueprintMemberLibrary::ForEachOverrideClass([this](const FClassReflection* InClassReflection)
			{
				OverrideClassNames.Add(FName(*InClassReflection->GetName()));
			});
		});
	}

	void RefreshLiveNodes()
	{
		TSet<UBlueprint*> ModifiedBlueprints;

		for (TObjectIterator<UK2Node_CSharpMemberBase> It; It; ++It)
		{
			const auto Node = *It;

			if (Node->IsTemplate() || Node->GetGraph() == nullptr || !IsValid(Node))
			{
				continue;
			}

			const auto Blueprint = FBlueprintEditorUtils::FindBlueprintForNode(Node);

			if (Blueprint == nullptr || Blueprint->bBeingCompiled)
			{
				continue;
			}

			if (Node->RefreshFromReflection())
			{
				Node->ReconstructNode();

				ModifiedBlueprints.Add(Blueprint);
			}
		}

		for (const auto Blueprint : ModifiedBlueprints)
		{
			FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
		}
	}

private:
	FDelegateHandle OnCompileHandle;

	FDelegateHandle OnCoreModuleActiveHandle;

	FDelegateHandle OnAssetLoadedHandle;

	FTSTicker::FDelegateHandle TickerHandle;

	TSet<FName> OverrideClassNames;
};

IMPLEMENT_MODULE(FUnrealCSharpBlueprintFunctionEditorModule, UnrealCSharpBlueprintFunctionEditor)
