#include "NewClass/ClassCollector.h"

#include "WidgetBlueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Setting/UnrealCSharpEditorSetting.h"

TArray<TSharedPtr<FDynamicClassViewerNode>> FClassCollector::AllNodes;

TSet<TSharedPtr<FDynamicClassViewerNode>, FDynamicClassViewerNodeKeyFuncs> FClassCollector::NodesSet;

FDelegateHandle FClassCollector::OnDynamicClassUpdatedRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnEndGeneratorRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnReloadCompleteRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnBlueprintCompiledRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnEndFrameRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnFilesLoadedRequestPopulateClassHierarchyDelegateHandle;

FDelegateHandle FClassCollector::OnAssetAddedDelegateHandle;

FDelegateHandle FClassCollector::OnAssetRemovedDelegateHandle;

FDelegateHandle FClassCollector::OnAssetRenamedDelegateHandle;

FClassCollector::FClassCollector()
{
	PopulateClassHierarchy();

	OnDynamicClassUpdatedRequestPopulateClassHierarchyDelegateHandle =
		FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.AddStatic(
			&FClassCollector::RequestPopulateClassHierarchy);

	OnEndGeneratorRequestPopulateClassHierarchyDelegateHandle =
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddStatic(
			&FClassCollector::RequestPopulateClassHierarchy);

	OnReloadCompleteRequestPopulateClassHierarchyDelegateHandle =
		FCoreUObjectDelegates::ReloadCompleteDelegate.AddStatic(
			&FClassCollector::OnReloadComplete);

	if (GEditor)
	{
		OnBlueprintCompiledRequestPopulateClassHierarchyDelegateHandle =
			GEditor->OnBlueprintCompiled().AddStatic(
				&FClassCollector::RequestPopulateClassHierarchy);
	}

	if (const auto AssetRegistryModule = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
	{
		OnFilesLoadedRequestPopulateClassHierarchyDelegateHandle =
			AssetRegistryModule->Get().OnFilesLoaded().AddStatic(
				&FClassCollector::RequestPopulateClassHierarchy);

		OnAssetAddedDelegateHandle =
			AssetRegistryModule->Get().OnAssetAdded().AddStatic(
				&FClassCollector::AssetAdded);

		OnAssetRemovedDelegateHandle =
			AssetRegistryModule->Get().OnAssetRemoved().AddStatic(
				&FClassCollector::RemoveAsset);

		OnAssetRenamedDelegateHandle =
			AssetRegistryModule->Get().OnAssetRenamed().AddStatic(
				&FClassCollector::OnAssetRenamed);
	}
}

FClassCollector::~FClassCollector()
{
	if (OnDynamicClassUpdatedRequestPopulateClassHierarchyDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.Remove(
			OnDynamicClassUpdatedRequestPopulateClassHierarchyDelegateHandle);
	}

	if (OnEndGeneratorRequestPopulateClassHierarchyDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(
			OnEndGeneratorRequestPopulateClassHierarchyDelegateHandle);
	}

	if (OnReloadCompleteRequestPopulateClassHierarchyDelegateHandle.IsValid())
	{
		FCoreUObjectDelegates::ReloadCompleteDelegate.Remove(
			OnReloadCompleteRequestPopulateClassHierarchyDelegateHandle);
	}

	if (GEditor)
	{
		if (OnBlueprintCompiledRequestPopulateClassHierarchyDelegateHandle.IsValid())
		{
			GEditor->OnBlueprintCompiled().Remove(
				OnBlueprintCompiledRequestPopulateClassHierarchyDelegateHandle);
		}
	}

	if (OnEndFrameRequestPopulateClassHierarchyDelegateHandle.IsValid())
	{
		FCoreDelegates::OnEndFrame.Remove(
			OnEndFrameRequestPopulateClassHierarchyDelegateHandle);
	}

	if (const auto AssetRegistryModule = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
	{
		if (OnFilesLoadedRequestPopulateClassHierarchyDelegateHandle.IsValid())
		{
			AssetRegistryModule->Get().OnFilesLoaded().Remove(OnFilesLoadedRequestPopulateClassHierarchyDelegateHandle);
		}

		if (OnAssetAddedDelegateHandle.IsValid())
		{
			AssetRegistryModule->Get().OnAssetAdded().Remove(OnAssetAddedDelegateHandle);
		}

		if (OnAssetRemovedDelegateHandle.IsValid())
		{
			AssetRegistryModule->Get().OnAssetRemoved().Remove(OnAssetRemovedDelegateHandle);
		}

		if (OnAssetRenamedDelegateHandle.IsValid())
		{
			AssetRegistryModule->Get().OnAssetRenamed().Remove(OnAssetRenamedDelegateHandle);
		}
	}
}

TArray<TSharedPtr<FDynamicClassViewerNode>>& FClassCollector::GetAllNodes()
{
	return AllNodes;
}

bool FClassCollector::ValidateNode(const FString& InClassName)
{
	return NodesSet.Contains(InClassName);
}

void FClassCollector::RequestPopulateClassHierarchy()
{
	static uint64 LastRequestFrame = 0;

	if (LastRequestFrame == GFrameNumber)
	{
		return;
	}

	LastRequestFrame = GFrameNumber;

	OnEndFrameRequestPopulateClassHierarchyDelegateHandle = FCoreDelegates::OnEndFrame.AddStatic(
		&FClassCollector::PopulateClassHierarchy);
}

void FClassCollector::PopulateClassHierarchy()
{
	PopulateClassInMemory();

	PopulateClassByAsset();

	RefreshAllNodes();
}

void FClassCollector::PopulateClassInMemory()

{
	TArray<UClass*> ValidClasses;

	for (TObjectIterator<UClass> ObjectIt; ObjectIt; ++ObjectIt)
	{
		auto CurrentClass = *ObjectIt;

		if (!IsValidParentClass(CurrentClass))
		{
			continue;
		}

		ValidClasses.Add(CurrentClass);
	}

	TArray<UClass*> FilterClasses;

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (!UnrealCSharpEditorSetting->IsGenerateAllModules())
		{
			auto SupportedModules = UnrealCSharpEditorSetting->GetSupportedModule();

			if (const int32 Index = SupportedModules.Find(FApp::GetProjectName()); Index != INDEX_NONE)
			{
				SupportedModules[Index] = TEXT("Game");
			}

			for (auto ValidClassIt = ValidClasses.CreateIterator(); ValidClassIt; ++ValidClassIt)
			{
				if (const auto CurrentClass = *ValidClassIt; SupportedModules.Contains(
					FUnrealCSharpFunctionLibrary::GetModuleName(CurrentClass)))
				{
					FilterClasses.Add(CurrentClass);
				}
			}
		}
		else
		{
			FilterClasses = ValidClasses;
		}
	}

	for (auto FilterClassIt = FilterClasses.CreateConstIterator(); FilterClassIt; ++FilterClassIt)
	{
		const auto CurrentClass = *FilterClassIt;

		TSharedPtr<FDynamicClassViewerNode> NewNode = MakeShared<FDynamicClassViewerNode>(
			CurrentClass->GetName(),
			CurrentClass->GetPathName()
		);

		NodesSet.Add(NewNode);
	}
}

void FClassCollector::PopulateClassByAsset()

{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		const auto& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(
			TEXT("AssetRegistry"));

		TArray<FName> AssetPaths;

		for (auto AssetPath : UnrealCSharpEditorSetting->GetSupportedAssetPath())
		{
			AssetPath = AssetPath == FApp::GetProjectName() ? TEXT("Game") : AssetPath;

			AssetPaths.Add(*FString::Printf(TEXT(
				"/%s"
			),
			                                *AssetPath));
		}

		TArray<FAssetData> AllAssetData;

		AssetRegistryModule.Get().GetAssetsByPaths(AssetPaths, AllAssetData, true);

		TArray<FName> SupportedAssetClassNames;

		for (const auto SupportedAssetClass : UnrealCSharpEditorSetting->GetSupportedAssetClass())
		{
			SupportedAssetClassNames.Add(SupportedAssetClass->GetFName());
		}

		for (const auto& AssetData : AllAssetData)
		{
			if (const auto& AssetDataClassName =
#if UE_ASSET_DATA_GET_ASSET_NAME
					AssetData.AssetClassPath.GetAssetName();
#else
					AssetData.AssetClass;
#endif

				SupportedAssetClassNames.Contains(AssetDataClassName))
			{
				if (AssetDataClassName == UBlueprint::StaticClass()->GetFName() ||
					AssetDataClassName == UWidgetBlueprint::StaticClass()->GetFName())
				{
					TSharedPtr<FDynamicClassViewerNode> NewNode = MakeShared<FDynamicClassViewerNode>(AssetData);

					NodesSet.Add(NewNode);
				}
			}
		}
	}
}

void FClassCollector::RefreshAllNodes()
{
	AllNodes.Empty();

	AllNodes.Append(NodesSet.Array());
}

bool FClassCollector::IsValidParentClass(const UClass* InClass)
{
	if (InClass == nullptr)
	{
		return false;
	}

	if (FUnrealCSharpFunctionLibrary::IsSpecialClass(InClass))
	{
		return false;
	}

	if (InClass->ClassGeneratedBy != nullptr && InClass != UBlueprintGeneratedClass::StaticClass() && InClass !=
		UWidgetBlueprint::StaticClass())
	{
		return false;
	}

	if (InClass->HasAnyClassFlags(
		CLASS_Interface | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_Hidden | CLASS_Transient))
	{
		return false;
	}

	if (!InClass->HasAnyClassFlags(CLASS_Native))
	{
		return false;
	}

	if (InClass->IsChildOf(UField::StaticClass()))
	{
		return false;
	}

	return true;
}

void FClassCollector::OnReloadComplete(EReloadCompleteReason Reason)
{
	RequestPopulateClassHierarchy();
}

void FClassCollector::AssetAdded(const FAssetData& InAssetData)
{
	if (const auto NewClassName = FDynamicNewClassUtils::GetAssetGeneratedClassName(InAssetData);
		ValidateNode(NewClassName))
	{
		return;
	}

	NodesSet.Add(MakeShared<FDynamicClassViewerNode>(InAssetData));

	RefreshAllNodes();
}

void FClassCollector::RemoveAsset(const FAssetData& InAssetData)
{
	const auto NewClassName = FDynamicNewClassUtils::GetAssetGeneratedClassName(InAssetData);

	if (!ValidateNode(NewClassName))
	{
		return;
	}

	NodesSet.Remove(NewClassName);

	RefreshAllNodes();
}

void FClassCollector::OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath)
{
	int LastPointIndex;

	InOldObjectPath.FindLastChar(TEXT('.'), LastPointIndex);

	if (LastPointIndex == INDEX_NONE)
	{
		return;
	}

	const auto OldClassName = InOldObjectPath.RightChop(LastPointIndex + 1).Append(TEXT("_C"));

	if (!ValidateNode(OldClassName))
	{
		return;
	}

	NodesSet.Remove(OldClassName);

	NodesSet.Add(MakeShared<FDynamicClassViewerNode>(InAssetData));

	RefreshAllNodes();
}
