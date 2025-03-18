#include "NewClass/ClassCollector.h"
#include "WidgetBlueprint.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpCoreModuleDelegates.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "UEVersion.h"

TArray<TSharedPtr<FDynamicClassViewerNode>> FClassCollector::AllNodes;

TSet<TSharedPtr<FDynamicClassViewerNode>, FDynamicClassViewerNodeKeyFuncs> FClassCollector::NodesSet;

FDelegateHandle FClassCollector::OnDynamicClassUpdatedDelegateHandle;

FDelegateHandle FClassCollector::OnEndGeneratorDelegateHandle;

FDelegateHandle FClassCollector::OnReloadCompleteDelegateDelegateHandle;

FDelegateHandle FClassCollector::OnBlueprintCompiledDelegateHandle;

FDelegateHandle FClassCollector::OnEndFrameDelegateHandle;

FDelegateHandle FClassCollector::OnFilesLoadedDelegateHandle;

FDelegateHandle FClassCollector::OnAssetAddedDelegateHandle;

FDelegateHandle FClassCollector::OnAssetRemovedDelegateHandle;

FDelegateHandle FClassCollector::OnAssetRenamedDelegateHandle;

FClassCollector::FClassCollector()
{
	PopulateClassHierarchy();

	OnDynamicClassUpdatedDelegateHandle =
		FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.AddStatic(
			&FClassCollector::RequestPopulateClassHierarchy);

	OnEndGeneratorDelegateHandle =
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.AddStatic(&FClassCollector::RequestPopulateClassHierarchy);

	OnReloadCompleteDelegateDelegateHandle =
		FCoreUObjectDelegates::ReloadCompleteDelegate.AddStatic(&FClassCollector::OnReloadComplete);

	if (GEditor)
	{
		OnBlueprintCompiledDelegateHandle =
			GEditor->OnBlueprintCompiled().AddStatic(&FClassCollector::RequestPopulateClassHierarchy);
	}

	if (const auto AssetRegistryModule = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
	{
		OnFilesLoadedDelegateHandle =
			AssetRegistryModule->Get().OnFilesLoaded().AddStatic(&FClassCollector::RequestPopulateClassHierarchy);

		OnAssetAddedDelegateHandle =
			AssetRegistryModule->Get().OnAssetAdded().AddStatic(&FClassCollector::OnAssetAdded);

		OnAssetRemovedDelegateHandle =
			AssetRegistryModule->Get().OnAssetRemoved().AddStatic(&FClassCollector::OnAssetRemoved);

		OnAssetRenamedDelegateHandle =
			AssetRegistryModule->Get().OnAssetRenamed().AddStatic(&FClassCollector::OnAssetRenamed);
	}
}

FClassCollector::~FClassCollector()
{
	if (OnDynamicClassUpdatedDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnDynamicClassUpdated.Remove(OnDynamicClassUpdatedDelegateHandle);
	}

	if (OnEndGeneratorDelegateHandle.IsValid())
	{
		FUnrealCSharpCoreModuleDelegates::OnEndGenerator.Remove(OnEndGeneratorDelegateHandle);
	}

	if (OnReloadCompleteDelegateDelegateHandle.IsValid())
	{
		FCoreUObjectDelegates::ReloadCompleteDelegate.Remove(OnReloadCompleteDelegateDelegateHandle);
	}

	if (GEditor)
	{
		if (OnBlueprintCompiledDelegateHandle.IsValid())
		{
			GEditor->OnBlueprintCompiled().Remove(OnBlueprintCompiledDelegateHandle);
		}
	}

	if (OnEndFrameDelegateHandle.IsValid())
	{
		FCoreDelegates::OnEndFrame.Remove(OnEndFrameDelegateHandle);
	}

	if (const auto AssetRegistryModule = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
	{
		if (OnFilesLoadedDelegateHandle.IsValid())
		{
			AssetRegistryModule->Get().OnFilesLoaded().Remove(OnFilesLoadedDelegateHandle);
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
	static auto LastRequestFrame = 0u;

	if (LastRequestFrame == GFrameNumber)
	{
		return;
	}

	LastRequestFrame = GFrameNumber;

	OnEndFrameDelegateHandle = FCoreDelegates::OnEndFrame.AddStatic(&FClassCollector::PopulateClassHierarchy);
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

	for (TObjectIterator<UClass> Class; Class; ++Class)
	{
		if (!IsValidParentClass(*Class))
		{
			continue;
		}

		ValidClasses.Add(*Class);
	}

	TArray<UClass*> FilterClasses;

	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		if (!UnrealCSharpEditorSetting->IsGenerateAllModules())
		{
			auto SupportedModules = UnrealCSharpEditorSetting->GetSupportedModule();

			if (const auto Index = SupportedModules.Find(FApp::GetProjectName()); Index != INDEX_NONE)
			{
				SupportedModules[Index] = TEXT("Game");
			}

			for (auto Class = ValidClasses.CreateIterator(); Class; ++Class)
			{
				if (SupportedModules.Contains(FUnrealCSharpFunctionLibrary::GetModuleName(*Class)))
				{
					FilterClasses.Add(*Class);
				}
			}
		}
		else
		{
			FilterClasses = ValidClasses;
		}
	}

	for (auto FilterClass = FilterClasses.CreateConstIterator(); FilterClass; ++FilterClass)
	{
		TSharedPtr<FDynamicClassViewerNode> Node = MakeShared<FDynamicClassViewerNode>(
			(*FilterClass)->GetName(),
			(*FilterClass)->GetPathName()
		);

		NodesSet.Add(Node);
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

		for (const auto& SupportedAssetClass : UnrealCSharpEditorSetting->GetSupportedAssetClass())
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
					TSharedPtr<FDynamicClassViewerNode> Node = MakeShared<FDynamicClassViewerNode>(AssetData);

					NodesSet.Add(Node);
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

	if (InClass->ClassGeneratedBy != nullptr &&
		InClass != UBlueprintGeneratedClass::StaticClass() &&
		InClass != UWidgetBlueprint::StaticClass())
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

void FClassCollector::OnReloadComplete(EReloadCompleteReason InReason)
{
	RequestPopulateClassHierarchy();
}

void FClassCollector::OnAssetAdded(const FAssetData& InAssetData)
{
	if (const auto NewClassName = FDynamicNewClassUtils::GetAssetGeneratedClassName(InAssetData);
		ValidateNode(NewClassName))
	{
		return;
	}

	NodesSet.Add(MakeShared<FDynamicClassViewerNode>(InAssetData));

	RefreshAllNodes();
}

void FClassCollector::OnAssetRemoved(const FAssetData& InAssetData)
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
