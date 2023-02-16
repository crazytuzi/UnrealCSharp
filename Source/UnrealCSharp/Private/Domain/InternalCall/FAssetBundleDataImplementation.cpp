#include "Domain/InternalCall/FAssetBundleDataImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterAssetBundleData
{
	FRegisterAssetBundleData()
	{
		TScriptStructBuilder<FAssetBundleData>(NAMESPACE_LIBRARY)
			.Function("Equality",
			          static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_InequalityImplementation))
			.Function("FindEntry",
			          static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_FindEntryImplementation))
			.Function("AddBundleAsset",
			          static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_AddBundleAssetImplementation))
			.Function("Reset", static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_ResetImplementation))
			.Function("ToDebugString",
			          static_cast<void*>(FAssetBundleDataImplementation::AssetBundleData_ToDebugStringImplementation))
			.Register();
	}
};

static FRegisterAssetBundleData RegisterAssetBundleData;

bool FAssetBundleDataImplementation::AssetBundleData_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleDataA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FAssetBundleData>(A);

	const auto AssetBundleDataB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FAssetBundleData>(B);

	if (AssetBundleDataA != nullptr && AssetBundleDataB != nullptr)
	{
		return AssetBundleDataA->operator==(*AssetBundleDataB);
	}

	return false;
}

bool FAssetBundleDataImplementation::AssetBundleData_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto AssetBundleDataA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FAssetBundleData>(A);

	const auto AssetBundleDataB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FAssetBundleData>(B);

	if (AssetBundleDataA != nullptr && AssetBundleDataB != nullptr)
	{
		return AssetBundleDataA->operator!=(*AssetBundleDataB);
	}

	return false;
}

void FAssetBundleDataImplementation::AssetBundleData_FindEntryImplementation(
	const MonoObject* InMonoObject, MonoObject* SearchName, MonoObject** OutValue)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FAssetBundleEntry)),
		CLASS_SCRIPT_STRUCT_NAME(FAssetBundleEntry));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutAssetBundleEntry = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FAssetBundleEntry>(NewMonoObject);

	if (AssetBundleData != nullptr && OutAssetBundleEntry != nullptr)
	{
		*OutAssetBundleEntry = *AssetBundleData->FindEntry(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(SearchName, nullptr)));
	}
}

void FAssetBundleDataImplementation::AssetBundleData_AddBundleAssetImplementation(
	const MonoObject* InMonoObject, MonoObject* BundleName, const MonoObject* AssetPath)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (AssetBundleData != nullptr && SoftObjectPath != nullptr)
	{
		AssetBundleData->AddBundleAsset(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(BundleName, nullptr)),
			*SoftObjectPath);
	}
}

void FAssetBundleDataImplementation::AssetBundleData_ResetImplementation(const MonoObject* InMonoObject)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	if (AssetBundleData != nullptr)
	{
		AssetBundleData->Reset();
	}
}

void FAssetBundleDataImplementation::AssetBundleData_ToDebugStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto AssetBundleData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FAssetBundleData>(InMonoObject);

	if (AssetBundleData != nullptr)
	{
		const auto ResultString = AssetBundleData->ToDebugString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
