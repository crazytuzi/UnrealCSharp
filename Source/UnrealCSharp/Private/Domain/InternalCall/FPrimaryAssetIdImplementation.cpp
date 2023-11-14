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

	const auto OutPrimaryAssetId = new FPrimaryAssetId(FPrimaryAssetId::ParseTypeAndName(FName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(TypeAndName, nullptr))))));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPrimaryAssetId>::Get(), OutPrimaryAssetId,
	                                                        NewMonoObject);
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameStringImplementation(
	MonoObject* TypeAndName, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FPrimaryAssetId, FPrimaryAssetId>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = new FPrimaryAssetId(FPrimaryAssetId::ParseTypeAndName(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(TypeAndName, nullptr))))));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPrimaryAssetId>::Get(), OutPrimaryAssetId,
	                                                        NewMonoObject);
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

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_FromStringImplementation(MonoObject* String, MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FPrimaryAssetId, FPrimaryAssetId>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = new FPrimaryAssetId(FPrimaryAssetId::FromString(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(String, nullptr))))));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPrimaryAssetId>::Get(), OutPrimaryAssetId,
	                                                        NewMonoObject);
}
