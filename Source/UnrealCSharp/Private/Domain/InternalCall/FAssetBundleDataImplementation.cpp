#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterAssetBundleData
{
	FRegisterAssetBundleData()
	{
		TReflectionClassBuilder<FAssetBundleData>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FAssetBundleData, const FAssetBundleData&))
			.Function("FindEntry",
			          BINDING_OVERLOAD(FAssetBundleEntry*(FAssetBundleData::*)(FName),
			                           &FAssetBundleData::FindEntry),
			          {"SearchName"})
			.Function("AddBundleAsset",
			          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const FSoftObjectPath&),
			                           &FAssetBundleData::AddBundleAsset),
			          {"BundleName", "AssetPath"})
			.Function("AddBundleAssets",
			          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const TArray<FSoftObjectPath>&),
			                           &FAssetBundleData::AddBundleAssets),
			          {"BundleName", "AssetPaths"})
			.Function("SetBundleAssets", BINDING_FUNCTION(&FAssetBundleData::SetBundleAssets),
			          {"BundleName", "AssetPaths"})
			.Function("Reset", BINDING_FUNCTION(&FAssetBundleData::Reset))
			.Function("ToDebugString", BINDING_FUNCTION(&FAssetBundleData::ToDebugString))
			.Register();
	}
};

static FRegisterAssetBundleData RegisterAssetBundleData;
