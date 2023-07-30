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
			.Function("Equality", FAssetBundleEntryImplementation::AssetBundleEntry_EqualityImplementation)
			.Function("Inequality", FAssetBundleEntryImplementation::AssetBundleEntry_InequalityImplementation)
			.Register();
	}
};

static FRegisterAssetBundleEntry RegisterAssetBundleEntry;

bool FAssetBundleEntryImplementation::AssetBundleEntry_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto AssetBundleEntry = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(InMonoObject);

	if (AssetBundleEntry != nullptr)
	{
		return AssetBundleEntry->IsValid();
	}

	return false;
}

bool FAssetBundleEntryImplementation::AssetBundleEntry_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleEntryA = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(A);

	const auto AssetBundleEntryB = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(B);

	if (AssetBundleEntryA != nullptr && AssetBundleEntryB != nullptr)
	{
		return AssetBundleEntryA->operator==(*AssetBundleEntryB);
	}

	return false;
}

bool FAssetBundleEntryImplementation::AssetBundleEntry_InequalityImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleEntryA = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(A);

	const auto AssetBundleEntryB = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(B);

	if (AssetBundleEntryA != nullptr && AssetBundleEntryB != nullptr)
	{
		return AssetBundleEntryA->operator!=(*AssetBundleEntryB);
	}

	return false;
}
