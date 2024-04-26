#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

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
			.Function("AddBundleAsset",
			          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const FSoftObjectPath&),
			                           &FAssetBundleData::AddBundleAsset,
			                           TArray<FString>{"BundleName", "AssetPath"}))
			.Function("AddBundleAssets",
			          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, const TArray<FSoftObjectPath>&),
			                           &FAssetBundleData::AddBundleAssets,
			                           TArray<FString>{"BundleName", "AssetPaths"}))
			.Function("SetBundleAssets",
			          BINDING_OVERLOAD(void(FAssetBundleData::*)(FName, TArray<FSoftObjectPath>&&),
			                           &FAssetBundleData::SetBundleAssets,
			                           TArray<FString>{"BundleName", "AssetPaths"}))
			.Function("Reset", BINDING_FUNCTION(&FAssetBundleData::Reset))
			.Function("ToDebugString", BINDING_FUNCTION(&FAssetBundleData::ToDebugString));
	}
};

static FRegisterAssetBundleData RegisterAssetBundleData;
