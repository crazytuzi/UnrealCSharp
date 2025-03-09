#pragma once

#include "CoreMinimal.h"
#include "SDynamicClassViewer.h"

struct FDynamicClassViewerNodeKeyFuncs : BaseKeyFuncs<TSharedPtr<FDynamicClassViewerNode>, FString>
{
	using FElementType = TSharedPtr<FDynamicClassViewerNode>;

	using FKeyType = FString;

	static FKeyType GetSetKey(const FElementType& InElement)
	{
		return InElement.IsValid() ? InElement->AssetClassName : TEXT("");
	}

	static bool Matches(const FKeyType& A, const FKeyType& B)
	{
		return A == B;
	}

	static uint32 GetKeyHash(const FKeyType& InKey)
	{
		return GetTypeHash(InKey);
	}
};

class FClassCollector final : public TSharedFromThis<FClassCollector>
{
public:
	FClassCollector();

	~FClassCollector();

	static TArray<TSharedPtr<FDynamicClassViewerNode>>& GetAllNodes();

	static bool ValidateNode(const FString& InClassName);

	static void RequestPopulateClassHierarchy();

private:
	static void PopulateClassHierarchy();

	static void PopulateClassInMemory();

	static void PopulateClassByAsset();

	static void RefreshAllNodes();

	static bool IsValidParentClass(const UClass* InClass);

	static void OnReloadComplete(EReloadCompleteReason InReason);

	static void OnAssetAdded(const FAssetData& InAssetData);

	static void OnAssetRemoved(const FAssetData& InAssetData);

	static void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldObjectPath);

private:
	static TArray<TSharedPtr<FDynamicClassViewerNode>> AllNodes;

	static TSet<TSharedPtr<FDynamicClassViewerNode>, FDynamicClassViewerNodeKeyFuncs> NodesSet;

	static FDelegateHandle OnDynamicClassUpdatedDelegateHandle;

	static FDelegateHandle OnEndGeneratorDelegateHandle;

	static FDelegateHandle OnReloadCompleteDelegateDelegateHandle;

	static FDelegateHandle OnBlueprintCompiledDelegateHandle;

	static FDelegateHandle OnEndFrameDelegateHandle;

	static FDelegateHandle OnFilesLoadedDelegateHandle;

	static FDelegateHandle OnAssetAddedDelegateHandle;

	static FDelegateHandle OnAssetRemovedDelegateHandle;

	static FDelegateHandle OnAssetRenamedDelegateHandle;
};
