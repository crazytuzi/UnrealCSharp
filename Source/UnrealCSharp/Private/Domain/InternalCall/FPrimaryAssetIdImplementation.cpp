#include "Domain/InternalCall/FPrimaryAssetIdImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPrimaryAssetId
{
	FRegisterPrimaryAssetId()
	{
		TReflectionClassBuilder<FPrimaryAssetId>(NAMESPACE_LIBRARY)
			.Function("ParseTypeAndNameName",
			          FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameNameImplementation)
			.Function("ParseTypeAndNameString",
			          FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameStringImplementation)
			.Function("IsValid", FPrimaryAssetIdImplementation::PrimaryAssetId_IsValidImplementation)
			.Function("ToString", FPrimaryAssetIdImplementation::PrimaryAssetId_ToStringImplementation)
			.Function("FromString", FPrimaryAssetIdImplementation::PrimaryAssetId_FromStringImplementation)
			.Function("Equality", FPrimaryAssetIdImplementation::PrimaryAssetId_EqualityImplementation)
			.Function("Inequality", FPrimaryAssetIdImplementation::PrimaryAssetId_InequalityImplementation)
			.Register();
	}
};

static FRegisterPrimaryAssetId RegisterPrimaryAssetId;

void FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameNameImplementation(
	MonoObject* TypeAndName, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FPrimaryAssetId, FPrimaryAssetId>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::ParseTypeAndName(FName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(TypeAndName, nullptr)))));
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameStringImplementation(
	MonoObject* TypeAndName, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FPrimaryAssetId, FPrimaryAssetId>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::ParseTypeAndName(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(TypeAndName, nullptr)))));
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_IsValidImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto PrimaryAssetId = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetId>(InGarbageCollectionHandle);

	if (PrimaryAssetId != nullptr)
	{
		return PrimaryAssetId->IsValid();
	}

	return false;
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PrimaryAssetId = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetId>(InGarbageCollectionHandle);

	if (PrimaryAssetId != nullptr)
	{
		const auto ResultString = PrimaryAssetId->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_FromStringImplementation(MonoObject* String, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FPrimaryAssetId, FPrimaryAssetId>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::FromString(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(String, nullptr)))));
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_EqualityImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto PrimaryAssetIdA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPrimaryAssetId>(A);

	const auto PrimaryAssetIdB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPrimaryAssetId>(B);

	if (PrimaryAssetIdA != nullptr && PrimaryAssetIdB != nullptr)
	{
		return PrimaryAssetIdA->operator==(*PrimaryAssetIdB);
	}

	return false;
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_InequalityImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto PrimaryAssetIdA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPrimaryAssetId>(A);

	const auto PrimaryAssetIdB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPrimaryAssetId>(B);

	if (PrimaryAssetIdA != nullptr && PrimaryAssetIdB != nullptr)
	{
		return PrimaryAssetIdA->operator!=(*PrimaryAssetIdB);
	}

	return false;
}
