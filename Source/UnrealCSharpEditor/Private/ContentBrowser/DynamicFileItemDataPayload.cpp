#include "ContentBrowser/DynamicFileItemDataPayload.h"
#include "ContentBrowserDataSource.h"

FDynamicFileItemDataPayload::FDynamicFileItemDataPayload(const FName& InInternalPath, UClass* InClass):
	InternalPath(InInternalPath),
	Class(InClass),
	AssetData(InClass)
{
}

bool FDynamicFileItemDataPayload::GetItemAttribute(const FName& InAttributeKey,
                                                   FContentBrowserItemDataAttributeValue& OutAttributeValue)
{
	if (InAttributeKey == ContentBrowserItemAttributes::ItemTypeDisplayName)
	{
		OutAttributeValue.SetValue(TEXT("DynamicClass"));

		return true;
	}

	return false;
}

const FName& FDynamicFileItemDataPayload::GetInternalPath() const
{
	return InternalPath;
}

UClass* FDynamicFileItemDataPayload::GetClass() const
{
	return Class.Get();
}

const FAssetData& FDynamicFileItemDataPayload::GetAssetData() const
{
	return AssetData;
}

void FDynamicFileItemDataPayload::UpdateThumbnail(FAssetThumbnail& OutThumbnail) const
{
	OutThumbnail.SetAsset(AssetData);
}
