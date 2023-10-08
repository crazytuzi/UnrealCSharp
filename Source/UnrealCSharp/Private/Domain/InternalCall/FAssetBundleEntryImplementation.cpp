#include "Domain/InternalCall/FAssetBundleEntryImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterAssetBundleEntry
{
	FRegisterAssetBundleEntry()
	{
		TReflectionClassBuilder<FAssetBundleEntry>(NAMESPACE_LIBRARY)
			.Function("IsValid", FAssetBundleEntryImplementation::AssetBundleEntry_IsValidImplementation)
			.Register();
	}
};

static FRegisterAssetBundleEntry RegisterAssetBundleEntry;

bool FAssetBundleEntryImplementation::AssetBundleEntry_IsValidImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto AssetBundleEntry = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(InGarbageCollectionHandle);

	if (AssetBundleEntry != nullptr)
	{
		return AssetBundleEntry->IsValid();
	}

	return false;
}
