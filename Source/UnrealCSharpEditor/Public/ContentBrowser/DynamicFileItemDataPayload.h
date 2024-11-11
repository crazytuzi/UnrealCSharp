#pragma once

#include "ContentBrowserItemData.h"
#include "Editor/UnrealEd/Public/AssetThumbnail.h"

class FDynamicFileItemDataPayload final : public IContentBrowserItemDataPayload
{
public:
	explicit FDynamicFileItemDataPayload(const FName& InInternalPath, UClass* InClass);

	static bool GetItemAttribute(const FName& InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);

	const FName& GetInternalPath() const;

	UClass* GetClass() const;

	const FAssetData& GetAssetData() const;

	void UpdateThumbnail(FAssetThumbnail& OutThumbnail) const;

private:
	FName InternalPath;

	TWeakObjectPtr<UClass> Class;

	FAssetData AssetData;
};
