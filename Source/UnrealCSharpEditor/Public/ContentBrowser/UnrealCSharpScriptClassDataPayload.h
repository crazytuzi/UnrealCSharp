#pragma once

#include "ContentBrowserItemData.h"
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

	//const FString& GetFilename() const;

private:
	FName InternalPath;

	mutable bool bHasCachedFilename = false;
	mutable FString CachedFilename;
};

class UNREALCSHARPEDITOR_API FUnrealCSharpScriptClassFileItemDataPayload : public IContentBrowserItemDataPayload
{
public:
	FUnrealCSharpScriptClassFileItemDataPayload(const FName InInternalPath, UClass* InClass);

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

	//const FString& GetFilename() const;

	void UpdateThumbnail(FAssetThumbnail& InThumbnail) const;

private:
	FName InternalPath;

	TWeakObjectPtr<UClass> Class;

	FAssetData AssetData;

	mutable bool bHasCachedFilename = false;
	mutable FString CachedFilename;
};