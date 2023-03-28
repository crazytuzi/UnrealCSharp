#include "Domain/InternalCall/FPrimaryAssetIdImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterPrimaryAssetId
{
	FRegisterPrimaryAssetId()
	{
		TScriptStructBuilder<FPrimaryAssetId>(NAMESPACE_LIBRARY)
			.Function("ParseTypeAndNameName",
			          static_cast<void*>(
				          FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameNameImplementation))
			.Function("ParseTypeAndNameString",
			          static_cast<void*>(
				          FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameStringImplementation))
			.Function("IsValid",
			          static_cast<void*>(FPrimaryAssetIdImplementation::PrimaryAssetId_IsValidImplementation))
			.Function("ToString",
			          static_cast<void*>(FPrimaryAssetIdImplementation::PrimaryAssetId_ToStringImplementation))
			.Function("FromString",
			          static_cast<void*>(FPrimaryAssetIdImplementation::PrimaryAssetId_FromStringImplementation))
			.Function("Equality",
			          static_cast<void*>(FPrimaryAssetIdImplementation::PrimaryAssetId_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FPrimaryAssetIdImplementation::PrimaryAssetId_InequalityImplementation))
			.Register();
	}
};

static FRegisterPrimaryAssetId RegisterPrimaryAssetId;

void FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameNameImplementation(
	MonoObject* TypeAndName, MonoObject** OutValue)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPrimaryAssetId)),
		CLASS_SCRIPT_STRUCT_NAME(FPrimaryAssetId));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::ParseTypeAndName(FName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment()->
			GetDomain()->Object_To_String(TypeAndName, nullptr)))));
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_ParseTypeAndNameStringImplementation(MonoObject* TypeAndName,
	MonoObject** OutValue)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPrimaryAssetId)),
		CLASS_SCRIPT_STRUCT_NAME(FPrimaryAssetId));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::ParseTypeAndName(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment()->
			GetDomain()->Object_To_String(TypeAndName, nullptr)))));
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto PrimaryAssetId = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPrimaryAssetId>(InMonoObject);

	if (PrimaryAssetId != nullptr)
	{
		return PrimaryAssetId->IsValid();
	}

	return false;
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_ToStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PrimaryAssetId = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPrimaryAssetId>(InMonoObject);

	if (PrimaryAssetId != nullptr)
	{
		const auto ResultString = PrimaryAssetId->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPrimaryAssetIdImplementation::PrimaryAssetId_FromStringImplementation(MonoObject* String, MonoObject** OutValue)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPrimaryAssetId)),
		CLASS_SCRIPT_STRUCT_NAME(FPrimaryAssetId));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPrimaryAssetId = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPrimaryAssetId>(NewMonoObject);

	*OutPrimaryAssetId = FPrimaryAssetId::FromString(FString(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment()->
			GetDomain()->Object_To_String(String, nullptr)))));
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PrimaryAssetIdA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FPrimaryAssetId>(A);

	const auto PrimaryAssetIdB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FPrimaryAssetId>(B);

	if (PrimaryAssetIdA != nullptr && PrimaryAssetIdB != nullptr)
	{
		return PrimaryAssetIdA->operator==(*PrimaryAssetIdB);
	}

	return false;
}

bool FPrimaryAssetIdImplementation::PrimaryAssetId_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PrimaryAssetIdA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FPrimaryAssetId>(A);

	const auto PrimaryAssetIdB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FPrimaryAssetId>(B);

	if (PrimaryAssetIdA != nullptr && PrimaryAssetIdB != nullptr)
	{
		return PrimaryAssetIdA->operator!=(*PrimaryAssetIdB);
	}

	return false;
}
