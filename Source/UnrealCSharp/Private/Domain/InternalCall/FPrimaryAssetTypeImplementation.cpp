#include "Domain/InternalCall/FPrimaryAssetTypeImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPrimaryAssetType
{
	FRegisterPrimaryAssetType()
	{
		TReflectionClassBuilder<FPrimaryAssetType>(NAMESPACE_LIBRARY)
			.Function("GetName", FPrimaryAssetTypeImplementation::PrimaryAssetType_GetNameImplementation)
			.Function("IsValid", FPrimaryAssetTypeImplementation::PrimaryAssetType_IsValidImplementation)
			.Function("ToString", FPrimaryAssetTypeImplementation::PrimaryAssetType_ToStringImplementation)
			.Register();
	}
};

static FRegisterPrimaryAssetType RegisterPrimaryAssetType;

void FPrimaryAssetTypeImplementation::PrimaryAssetType_GetNameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InGarbageCollectionHandle);

	if (PrimaryAssetType != nullptr)
	{
		const auto ResultString = PrimaryAssetType->GetName();

		const auto FoundMonoClass = TPropertyClass<FName, FName>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FPrimaryAssetTypeImplementation::PrimaryAssetType_IsValidImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InGarbageCollectionHandle);

	if (PrimaryAssetType != nullptr)
	{
		return PrimaryAssetType->IsValid();
	}

	return false;
}

void FPrimaryAssetTypeImplementation::PrimaryAssetType_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InGarbageCollectionHandle);

	if (PrimaryAssetType != nullptr)
	{
		const auto ResultString = PrimaryAssetType->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
