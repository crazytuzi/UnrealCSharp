#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"

namespace
{
	struct FRegisterAssetBundleData
	{
		FRegisterAssetBundleData()
		{
			TBindingClassBuilder<FAssetBundleData>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FAssetBundleData, const FAssetBundleData&))
				.Function("FindEntry",
				          BINDING_OVERLOAD(FAssetBundleEntry*(FAssetBundleData::*)(FName),
				                           &FAssetBundleData::FindEntry,
				                           TArray<FString>{"SearchName"}))
#if UE_ASSET_BUNDLE_DATA_ADD_BUNDLE_ASSET
				.Function("AddBundleAsset",
				          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const FSoftObjectPath&),
				                           &FAssetBundleData::AddBundleAsset,
				                           TArray<FString>{"BundleName", "AssetPath"}))
#endif
#if UE_ASSET_BUNDLE_DATA_ADD_BUNDLE_ASSETS
				.Function("AddBundleAssets",
				          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const TArray<FSoftObjectPath>&),
				                           &FAssetBundleData::AddBundleAssets,
				                           TArray<FString>{"BundleName", "AssetPaths"}))
#endif
#if UE_ASSET_BUNDLE_DATA_SET_BUNDLE_ASSETS
				.Function("SetBundleAssets",
				          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, TArray<FSoftObjectPath>&&),
				                           &FAssetBundleData::SetBundleAssets,
				                           TArray<FString>{"BundleName", "AssetPaths"}))
#endif
				.Function("Reset", BINDING_FUNCTION(&FAssetBundleData::Reset))
				.Function("ToDebugString", BINDING_FUNCTION(&FAssetBundleData::ToDebugString));
		}
	};

	FRegisterAssetBundleData RegisterAssetBundleData;
}
