#include "Domain/InternalCall/FAssetBundleDataImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterAssetBundleData
{
	FRegisterAssetBundleData()
	{
		TReflectionClassBuilder<FAssetBundleData>(NAMESPACE_LIBRARY)
			.Function("Equality", FAssetBundleDataImplementation::AssetBundleData_EqualityImplementation)
			.Function("Inequality", FAssetBundleDataImplementation::AssetBundleData_InequalityImplementation)
			.Function("FindEntry", FAssetBundleDataImplementation::AssetBundleData_FindEntryImplementation)
			.Function("AddBundleAsset", FAssetBundleDataImplementation::AssetBundleData_AddBundleAssetImplementation)
			.Function("Reset", FAssetBundleDataImplementation::AssetBundleData_ResetImplementation)
			.Function("ToDebugString", FAssetBundleDataImplementation::AssetBundleData_ToDebugStringImplementation)
			.Register();
	}
};

static FRegisterAssetBundleData RegisterAssetBundleData;

bool FAssetBundleDataImplementation::AssetBundleData_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleDataA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FAssetBundleData>(A);

	const auto AssetBundleDataB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FAssetBundleData>(B);

	if (AssetBundleDataA != nullptr && AssetBundleDataB != nullptr)
	{
		return AssetBundleDataA->operator==(*AssetBundleDataB);
	}

	return false;
}

bool FAssetBundleDataImplementation::AssetBundleData_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleDataA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FAssetBundleData>(A);

	const auto AssetBundleDataB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FAssetBundleData>(B);

	if (AssetBundleDataA != nullptr && AssetBundleDataB != nullptr)
	{
		return AssetBundleDataA->operator!=(*AssetBundleDataB);
	}

	return false;
}

void FAssetBundleDataImplementation::AssetBundleData_FindEntryImplementation(
	const MonoObject* InMonoObject, MonoObject* SearchName, MonoObject** OutValue)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FAssetBundleEntry, FAssetBundleEntry>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutAssetBundleEntry = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleEntry>(NewMonoObject);

	if (AssetBundleData != nullptr && OutAssetBundleEntry != nullptr)
	{
		*OutAssetBundleEntry = *AssetBundleData->FindEntry(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(SearchName, nullptr))));
	}
}

void FAssetBundleDataImplementation::AssetBundleData_AddBundleAssetImplementation(
	const MonoObject* InMonoObject, MonoObject* BundleName, const MonoObject* AssetPath)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (AssetBundleData != nullptr && SoftObjectPath != nullptr)
	{
		AssetBundleData->AddBundleAsset(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(BundleName, nullptr))), *SoftObjectPath);
	}
}

void FAssetBundleDataImplementation::AssetBundleData_ResetImplementation(const MonoObject* InMonoObject)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	if (AssetBundleData != nullptr)
	{
		AssetBundleData->Reset();
	}
}

void FAssetBundleDataImplementation::AssetBundleData_ToDebugStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	if (AssetBundleData != nullptr)
	{
		const auto ResultString = AssetBundleData->ToDebugString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
