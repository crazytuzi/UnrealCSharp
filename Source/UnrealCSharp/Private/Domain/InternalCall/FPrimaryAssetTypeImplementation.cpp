#include "Domain/InternalCall/FPrimaryAssetTypeImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPrimaryAssetType
{
	FRegisterPrimaryAssetType()
	{
		TScriptStructBuilder<FPrimaryAssetType>(NAMESPACE_LIBRARY)
			.Function("GetName",
			          static_cast<void*>(FPrimaryAssetTypeImplementation::PrimaryAssetType_GetNameImplementation))
			.Function("Equality",
			          static_cast<void*>(FPrimaryAssetTypeImplementation::PrimaryAssetType_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FPrimaryAssetTypeImplementation::PrimaryAssetType_InequalityImplementation))
			.Function("IsValid",
			          static_cast<void*>(FPrimaryAssetTypeImplementation::PrimaryAssetType_IsValidImplementation))
			.Function("ToString",
			          static_cast<void*>(FPrimaryAssetTypeImplementation::PrimaryAssetType_ToStringImplementation))
			.Register();
	}
};

static FRegisterPrimaryAssetType RegisterPrimaryAssetType;

void FPrimaryAssetTypeImplementation::PrimaryAssetType_GetNameImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InMonoObject);

	if (PrimaryAssetType != nullptr)
	{
		const auto ResultString = PrimaryAssetType->GetName();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_NAME);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FPrimaryAssetTypeImplementation::PrimaryAssetType_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PrimaryAssetTypeA = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(A);

	const auto PrimaryAssetTypeB = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(B);

	if (PrimaryAssetTypeA != nullptr && PrimaryAssetTypeB != nullptr)
	{
		return PrimaryAssetTypeA->operator==(*PrimaryAssetTypeB);
	}

	return false;
}

bool FPrimaryAssetTypeImplementation::PrimaryAssetType_InequalityImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto PrimaryAssetTypeA = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(A);

	const auto PrimaryAssetTypeB = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(B);

	if (PrimaryAssetTypeA != nullptr && PrimaryAssetTypeB != nullptr)
	{
		return PrimaryAssetTypeA->operator!=(*PrimaryAssetTypeB);
	}

	return false;
}

bool FPrimaryAssetTypeImplementation::PrimaryAssetType_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InMonoObject);

	if (PrimaryAssetType != nullptr)
	{
		return PrimaryAssetType->IsValid();
	}

	return false;
}

void FPrimaryAssetTypeImplementation::PrimaryAssetType_ToStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PrimaryAssetType = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPrimaryAssetType>(InMonoObject);

	if (PrimaryAssetType != nullptr)
	{
		const auto ResultString = PrimaryAssetType->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
