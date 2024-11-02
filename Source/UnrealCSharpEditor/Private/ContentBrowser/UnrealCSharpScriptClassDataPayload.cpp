#pragma once

#include "UnrealCSharpEditor/Public/ContentBrowser/UnrealCSharpScriptClassDataPayload.h"


FUnrealCSharpScriptClassFileItemDataPayload::FUnrealCSharpScriptClassFileItemDataPayload(const FName InInternalPath,
	UClass* InClass)
: InternalPath(InInternalPath)
	, Class(InClass)
	, AssetData(InClass)
{
}

void FUnrealCSharpScriptClassFileItemDataPayload::UpdateThumbnail(FAssetThumbnail& InThumbnail) const
{
	InThumbnail.SetAsset(AssetData);
}
