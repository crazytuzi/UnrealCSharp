#pragma once

#include "CoreMinimal.h"
#include "ContentBrowserDataSource.h"
#include "UnrealCSharpScriptClassDataPayload.h"
#include "IAssetTypeActions.h"
#include "ICollectionManager.h"
#include "ScriptClassHierarchy.h"

#include "UnrealCSharpScriptClassDataSource.generated.h"

#define SCRIPT_CLASS_ROOT_INTERNAL_PATH "/Classes_Script"

#define SCRIPT_CLASS_ROOT_VIRTUAL_PATH "/All/Classes_Script"

USTRUCT()
struct UNREALCSHARPEDITOR_API FUnrealCSharpCompiledScriptClassDataFilter
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSet<TObjectPtr<UClass>> ValidClasses;

	UPROPERTY()
	TSet<FName> ValidFolders;
};

UCLASS()
class UNREALCSHARPEDITOR_API UUnrealCSharpScriptClassDataSource : public UContentBrowserDataSource
{
	GENERATED_BODY()

public:
	void Initialize(const bool InAutoRegister = true);

	virtual void Shutdown() override;

	virtual void CompileFilter(const FName InPath, const FContentBrowserDataFilter& InFilter,
	                           FContentBrowserDataCompiledFilter& OutCompiledFilter) override;

	void OnScriptClassHierarchyUpdated();

	virtual void EnumerateItemsMatchingFilter(const FContentBrowserDataCompiledFilter& InFilter,
	                                          TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual void EnumerateItemsAtPath(const FName InPath, const EContentBrowserItemTypeFilter InItemTypeFilter,
	                                  TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual bool EnumerateItemsForObjects(const TArrayView<UObject*> InObjects,
	                                      TFunctionRef<bool(FContentBrowserItemData&&)> InCallback) override;

	virtual bool DoesItemPassFilter(const FContentBrowserItemData& InItem,
	                                const FContentBrowserDataCompiledFilter& InFilter) override;

	static FName GetClassModuleName(const UClass* InClass);

	static TSet<FName> GetGameModules();

	static FString GetDynamicClassSourcePath(const UClass* InClass);

	static FString GetDynamicClassVirtualPath(const UClass* InClass);

	static bool RootPathFilter(const FName& InPath);

	static bool RootPathFilter(const FString& InPath);

	static bool ConvertRelativePathToVirtualPath(const FName InNativePath, FName& OutVirtualPath);

	static bool EnumerateSubPaths(const FString& InPath, const TFunctionRef<bool(FName)>& InCallback);

	virtual bool CanEditItem(const FContentBrowserItemData& InItem, FText* OutErrorMsg) override;

	virtual bool EditItem(const FContentBrowserItemData& InItem) override;

	virtual bool BulkEditItems(TArrayView<const FContentBrowserItemData> InItems) override;

	virtual bool UpdateThumbnail(const FContentBrowserItemData& InItem, FAssetThumbnail& InThumbnail) override;

	virtual bool GetItemAttribute(const FContentBrowserItemData& InItem, const bool InIncludeMetaData,
	                              const FName InAttributeKey,
	                              FContentBrowserItemDataAttributeValue& OutAttributeValue) override;

	virtual bool GetItemAttributes(const FContentBrowserItemData& InItem, const bool InIncludeMetaData,
	                               FContentBrowserItemDataAttributeValues& OutAttributeValues) override;

	virtual bool AppendItemReference(const FContentBrowserItemData& InItem, FString& InOutStr) override;

	virtual bool TryGetCollectionId(const FContentBrowserItemData& InItem, FSoftObjectPath& OutCollectionId) override;

	virtual bool Legacy_TryGetPackagePath(const FContentBrowserItemData& InItem, FName& OutPackagePath) override;

	virtual bool Legacy_TryGetAssetData(const FContentBrowserItemData& InItem, FAssetData& OutAssetData) override;

	virtual bool Legacy_TryConvertPackagePathToVirtualPath(const FName InPackagePath, FName& OutPath) override;

	virtual bool Legacy_TryConvertAssetDataToVirtualPath(const FAssetData& InAssetData, const bool InUseFolderPaths,
	                                                     FName& OutPath) override;

protected:
	TSharedPtr<IAssetTypeActions> GetClassTypeActions();

	static bool RootClassPathPassesFilter(const FName InRootClassPath);

	virtual void BuildRootPathVirtualTree() override;

private:
	TSharedPtr<const FUnrealCSharpScriptClassFileItemDataPayload> GetClassFileItemPayload(
		const FContentBrowserItemData& InItem) const;

	TSharedPtr<const FUnrealCSharpScriptClassFolderItemDataPayload> GetClassFolderItemDataPayload(
		const FContentBrowserItemData& InItem) const;

	FContentBrowserItemData CreateClassFolderItem(const FName InFolderPath);

	FContentBrowserItemData CreateClassFileItem(UClass* InClass);

	bool GetClassPathsForCollections(TArrayView<const FCollectionNameType> InCollections,
	                                 const bool bIncludeChildCollections,
	                                 TArray<FTopLevelAssetPath>& OutClassPaths) const;

	TSharedPtr<IAssetTypeActions> ClassTypeActions;

	TSharedPtr<FScriptClassHierarchy> ScriptClassHierarchy;

	ICollectionManager* CollectionManager;
};
