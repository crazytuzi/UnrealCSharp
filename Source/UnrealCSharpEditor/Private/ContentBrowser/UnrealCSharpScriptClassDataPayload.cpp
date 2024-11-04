#pragma once

#include "UnrealCSharpEditor/Public/ContentBrowser/UnrealCSharpScriptClassDataPayload.h"

#include "ContentBrowserDataSource.h"


FUnrealCSharpScriptClassFileItemDataPayload::FUnrealCSharpScriptClassFileItemDataPayload(const FName InInternalPath,
	UClass* InClass)
: InternalPath(InInternalPath)
	, Class(InClass)
	, AssetData(InClass)
{
}

bool FUnrealCSharpScriptClassFileItemDataPayload::GetClassFileItemAttribute(IAssetTypeActions* InClassTypeActions,
	const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue)
{
	if (InAttributeKey == ContentBrowserItemAttributes::ItemTypeDisplayName)
	{
		OutAttributeValue.SetValue(TEXT("C# Dynamic Class"));
		
		return true;
	}

	return false;
}

void FUnrealCSharpScriptClassFileItemDataPayload::UpdateThumbnail(FAssetThumbnail& InThumbnail) const
{
	InThumbnail.SetAsset(AssetData);
}
