#include "Domain/InternalCall/FSoftObjectPathImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStructPropertyClass.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftObjectPath
{
	FRegisterSoftObjectPath()
	{
		TReflectionClassBuilder<FSoftObjectPath>(NAMESPACE_LIBRARY)
			.Function("ToString",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_ToStringImplementation))
			.Function("GetAssetPathName",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathNameImplementation))
			.Function("GetAssetPathString",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathStringImplementation))
			.Function("GetSubPathString",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_GetSubPathStringImplementation))
			.Function("GetLongPackageName",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_GetLongPackageNameImplementation))
			.Function("GetAssetName",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_GetAssetNameImplementation))
			.Function("SetPathName",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_SetPathNameImplementation))
			.Function("SetPathString",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_SetPathStringImplementation))
			.Function("Reset", static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_ResetImplementation))
			.Function("IsValid",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_IsValidImplementation))
			.Function("IsNull", static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_IsNullImplementation))
			.Function("IsAsset",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_IsAssetImplementation))
			.Function("IsSubobject",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_IsSubobjectImplementation))
			.Function("Equality",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_InequalityImplementation))
			.Function("FixupForPIE",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEImplementation))
			.Function("FixupForPIEInstance",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEInstanceImplementation))
			.Function("FixupCoreRedirects",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_FixupCoreRedirectsImplementation))
			.Function("GetCurrentTag",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_GetCurrentTagImplementation))
			.Function("InvalidateTag",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_InvalidateTagImplementation))
			.Function("GetOrCreateIDForObject",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_GetOrCreateIDForObjectImplementation))
			.Function("AddPIEPackageName",
			          static_cast<void*>(FSoftObjectPathImplementation::SoftObjectPath_AddPIEPackageNameImplementation))
			.Function("ClearPIEPackageNames",
			          static_cast<void*>(
				          FSoftObjectPathImplementation::SoftObjectPath_ClearPIEPackageNamesImplementation))
			.Register();
	}
};

static FRegisterSoftObjectPath RegisterSoftObjectPath;

void FSoftObjectPathImplementation::SoftObjectPath_ToStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathNameImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->GetAssetPathName();

		const auto FoundMonoClass = TPropertyClass<FName, FName>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->GetAssetPathString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_GetSubPathStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->GetSubPathString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_GetLongPackageNameImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->GetLongPackageName();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_GetAssetNameImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		const auto ResultString = SoftObjectPath->GetAssetName();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_SetPathNameImplementation(
	const MonoObject* InMonoObject, MonoObject* Path)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr && Path != nullptr)
	{
		return SoftObjectPath->SetPath(FName(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(Path, nullptr)))));
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_SetPathStringImplementation(
	const MonoObject* InMonoObject, MonoObject* Path)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr && Path != nullptr)
	{
		return SoftObjectPath->SetPath(FString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(Path, nullptr)))));
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_ResetImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		SoftObjectPath->Reset();
	}
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsValid();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsNullImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsNull();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsAssetImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsAsset();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsSubobjectImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsSubobject();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto SoftObjectPathA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(A);

	const auto SoftObjectPathB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(B);

	if (SoftObjectPathA != nullptr && SoftObjectPathB)
	{
		return SoftObjectPathA->operator==(*SoftObjectPathB);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto SoftObjectPathA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(A);

	const auto SoftObjectPathB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(B);

	if (SoftObjectPathA != nullptr && SoftObjectPathB)
	{
		return SoftObjectPathA->operator!=(*SoftObjectPathB);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->FixupForPIE();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEInstanceImplementation(
	const MonoObject* InMonoObject, const int32 PIEInstance)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->FixupForPIE(PIEInstance);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupCoreRedirectsImplementation(const MonoObject* InMonoObject)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InMonoObject);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->FixupCoreRedirects();
	}

	return false;
}

int32 FSoftObjectPathImplementation::SoftObjectPath_GetCurrentTagImplementation()
{
	return FSoftObjectPath::GetCurrentTag();
}

int32 FSoftObjectPathImplementation::SoftObjectPath_InvalidateTagImplementation()
{
	return FSoftObjectPath::InvalidateTag();
}

void FSoftObjectPathImplementation::SoftObjectPath_GetOrCreateIDForObjectImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FSoftObjectPath, FSoftObjectPath>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutSoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(NewMonoObject);

	if (FoundObject != nullptr && OutSoftObjectPath != nullptr)
	{
		*OutSoftObjectPath = FSoftObjectPath::GetOrCreateIDForObject(FoundObject);
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_AddPIEPackageNameImplementation(MonoObject* NewPIEPackageName)
{
	FSoftObjectPath::AddPIEPackageName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(NewPIEPackageName, nullptr))));
}

void FSoftObjectPathImplementation::SoftObjectPath_ClearPIEPackageNamesImplementation()
{
	FSoftObjectPath::ClearPIEPackageNames();
}
