#pragma once

#include "CoreMinimal.h"
#include "ContentBrowserDataSource.h"
#include "ICollectionManager.h"
#include "DynamicHierarchy.h"
#include "DynamicFileItemDataPayload.h"
#include "DynamicFolderItemDataPayload.h"
#include "UEVersion.h"
#include "DynamicDataSource.generated.h"

USTRUCT()
struct FDynamicDataFilter
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<TObjectPtr<UClass>> Classes;

	UPROPERTY()
	TSet<FName> Folders;
};

UCLASS()
class UDynamicDataSource : public UContentBrowserDataSource
{
	GENERATED_BODY()

public:
	void Initialize(const bool InAutoRegister = true);

	virtual void Shutdown() override;

	virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter,
	                           FContentBrowserDataCompiledFilter& OutCompiledFilter) override;

	virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter,
	                                          TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter,
	                                  TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual bool EnumerateItemsForObjects(const TArrayView<UObject*> InObjects,
	                                      TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem,
	                                const FContentBrowserDataCompiledFilter& InFilter) override;

	virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData,
	                              const FName InAttributeKey,
	                              FContentBrowserItemDataAttributeValue& OutAttributeValue) override;

	virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;

	virtual bool EditItem(const FContentBrowserItemData& InItem) override;

	virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;

	virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr) override;

	virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;

#if UE_TRY_GET_COLLECTION_ID_F_SOFT_OBJECT_PATH
	virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FName& OutCollectionId) override;
#else
	virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId) override;
#endif

	virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath) override;

	virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData) override;

	virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath) override;

	virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths,
	                                                     FName& OutPath) override;

	virtual void BuildRootPathVirtualTree() override;

private:
	static void OnNewClassRequested(const FName& InSelectedPath);

	void PopulateAddNewContextMenu(UToolMenu* InMenu);

	void OnDynamicClassUpdated();

	void OnEndGenerator();

	void UpdateHierarchy();

	static bool IsRootInternalPath(const FName& InPath);

	static FString GetVirtualPath(const UClass* InClass);

	TSharedPtr<const FDynamicFileItemDataPayload> GetFileItemDataPayload(
		const FContentBrowserItemData& InItemData) const;

	TSharedPtr<const FDynamicFolderItemDataPayload> GetFolderItemDataPayload(
		const FContentBrowserItemData& InItemData) const;

	FContentBrowserItemData CreateFolderItem(const FName& InFolderPath);

	FContentBrowserItemData CreateFileItem(UClass* InClass);

	bool GetClassPaths(const TArrayView<const FCollectionNameType>& InCollections,
	                   const bool bIncludeChildCollections,
#if UE_F_TOP_LEVEL_ASSET_PATH
	                   TArray<FTopLevelAssetPath>& OutClassPaths) const;
#else
	                   TArray<FName>& OutClassPaths) const;
#endif

private:
	FDelegateHandle OnDynamicClassUpdatedHandle;

	FDelegateHandle OnEndGeneratorHandle;

	TSharedPtr<FDynamicHierarchy> DynamicHierarchy;

	ICollectionManager* CollectionManager;
};
