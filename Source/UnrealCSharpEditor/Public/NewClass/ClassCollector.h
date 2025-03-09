#pragma once

#include "CoreMinimal.h"
#include "SDynamicClassViewer.h"

struct FDynamicClassViewerNodeKeyFuncs : BaseKeyFuncs<TSharedPtr<FDynamicClassViewerNode>, FString>
{
	using ElementType = TSharedPtr<FDynamicClassViewerNode>;

	using KeyType = FString;

	static KeyType GetSetKey(const ElementType& Element)
	{
		return Element.IsValid() ? Element->AssetClassName : TEXT("");
	}

	static bool Matches(const KeyType& A, const KeyType& B)
	{
		return A == B;
	}

	static uint32 GetKeyHash(const KeyType& Key)
	{
		return GetTypeHash(Key);
	}
};

using NodeSearcher = TSet<TSharedPtr<FDynamicClassViewerNode>, FDynamicClassViewerNodeKeyFuncs>;

class FClassCollector : public TSharedFromThis<FClassCollector>
{
public:
	FClassCollector();

	virtual ~FClassCollector();

	static TArray<TSharedPtr<FDynamicClassViewerNode>>& GetAllNodes();

	static bool ValidateNode(const FString& InClassName);

	static void RequestPopulateClassHierarchy();

private:
	static void PopulateClassHierarchy();

	static void PopulateClassInMemory();

	static void PopulateClassByAsset();

	static void RefreshAllNodes();

	static bool IsValidParentClass(const UClass* InClass);

	static void OnReloadComplete(EReloadCompleteReason Reason);

	static void AssetAdded(const FAssetData& InAssetData);

	static void RemoveAsset(const FAssetData& InAssetData);

	static void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);

private:
	static TArray<TSharedPtr<FDynamicClassViewerNode>> AllNodes;

	static TSet<TSharedPtr<FDynamicClassViewerNode>, FDynamicClassViewerNodeKeyFuncs> NodesSet;

	static FDelegateHandle OnDynamicClassUpdatedRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnEndGeneratorRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnReloadCompleteRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnBlueprintCompiledRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnEndFrameRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnFilesLoadedRequestPopulateClassHierarchyDelegateHandle;

	static FDelegateHandle OnAssetAddedDelegateHandle;

	static FDelegateHandle OnAssetRemovedDelegateHandle;

	static FDelegateHandle OnAssetRenamedDelegateHandle;
};
