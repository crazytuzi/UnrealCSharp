#pragma once

#include "ContentBrowserItemData.h"
#include "IAssetTypeActions.h"
#include "AssetRegistry/AssetData.h"

class FAssetThumbnail;

class UNREALCSHARPEDITOR_API FUnrealCSharpScriptClassFolderItemDataPayload : public IContentBrowserItemDataPayload
{
public:
	explicit FUnrealCSharpScriptClassFolderItemDataPayload(const FName InInternalPath)
		: InternalPath(InInternalPath)
	{
	}

	FName GetInternalPath() const
	{
		return InternalPath;
	}

private:
	FName InternalPath;
	
};

class UNREALCSHARPEDITOR_API FUnrealCSharpScriptClassFileItemDataPayload : public IContentBrowserItemDataPayload
{
public:
	FUnrealCSharpScriptClassFileItemDataPayload(const FName InInternalPath, UClass* InClass);

	static bool GetClassFileItemAttribute(IAssetTypeActions* InClassTypeActions, const bool InIncludeMetaData, const FName InAttributeKey, FContentBrowserItemDataAttributeValue& OutAttributeValue);

	FName GetInternalPath() const
	{
		return InternalPath;
	}

	UClass* GetClass() const
	{
		return Class.Get();
	}

	const FAssetData& GetAssetData() const
	{
		return AssetData;
	}
	
	void UpdateThumbnail(FAssetThumbnail& InThumbnail) const;

private:
	FName InternalPath;

	TWeakObjectPtr<UClass> Class;

	FAssetData AssetData;
	
};