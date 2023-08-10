#include "Domain/InternalCall/FSoftObjectPathImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftObjectPath
{
	FRegisterSoftObjectPath()
	{
		TReflectionClassBuilder<FSoftObjectPath>(NAMESPACE_LIBRARY)
			.Function("ToString", FSoftObjectPathImplementation::SoftObjectPath_ToStringImplementation)
			.Function("GetAssetPathName", FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathNameImplementation)
			.Function("GetAssetPathString",
			          FSoftObjectPathImplementation::SoftObjectPath_GetAssetPathStringImplementation)
			.Function("GetSubPathString", FSoftObjectPathImplementation::SoftObjectPath_GetSubPathStringImplementation)
			.Function("GetLongPackageName",
			          FSoftObjectPathImplementation::SoftObjectPath_GetLongPackageNameImplementation)
			.Function("GetAssetName", FSoftObjectPathImplementation::SoftObjectPath_GetAssetNameImplementation)
			.Function("SetPathName", FSoftObjectPathImplementation::SoftObjectPath_SetPathNameImplementation)
			.Function("SetPathString", FSoftObjectPathImplementation::SoftObjectPath_SetPathStringImplementation)
			.Function("Reset", FSoftObjectPathImplementation::SoftObjectPath_ResetImplementation)
			.Function("IsValid", FSoftObjectPathImplementation::SoftObjectPath_IsValidImplementation)
			.Function("IsNull", FSoftObjectPathImplementation::SoftObjectPath_IsNullImplementation)
			.Function("IsAsset", FSoftObjectPathImplementation::SoftObjectPath_IsAssetImplementation)
			.Function("IsSubobject", FSoftObjectPathImplementation::SoftObjectPath_IsSubobjectImplementation)
			.Function("Equality", FSoftObjectPathImplementation::SoftObjectPath_EqualityImplementation)
			.Function("Inequality", FSoftObjectPathImplementation::SoftObjectPath_InequalityImplementation)
			.Function("FixupForPIE", FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEImplementation)
			.Function("FixupForPIEInstance",
			          FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEInstanceImplementation)
			.Function("FixupCoreRedirects",
			          FSoftObjectPathImplementation::SoftObjectPath_FixupCoreRedirectsImplementation)
			.Function("GetCurrentTag", FSoftObjectPathImplementation::SoftObjectPath_GetCurrentTagImplementation)
			.Function("InvalidateTag", FSoftObjectPathImplementation::SoftObjectPath_InvalidateTagImplementation)
			.Function("GetOrCreateIDForObject",
			          FSoftObjectPathImplementation::SoftObjectPath_GetOrCreateIDForObjectImplementation)
			.Function("AddPIEPackageName",
			          FSoftObjectPathImplementation::SoftObjectPath_AddPIEPackageNameImplementation)
			.Function("ClearPIEPackageNames",
			          FSoftObjectPathImplementation::SoftObjectPath_ClearPIEPackageNamesImplementation)
			.Register();
	}
};

static FRegisterSoftObjectPath RegisterSoftObjectPath;

void FSoftObjectPathImplementation::SoftObjectPath_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* Path)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr && Path != nullptr)
	{
		return SoftObjectPath->SetPath(FName(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(Path, nullptr)))));
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_SetPathStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* Path)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr && Path != nullptr)
	{
		return SoftObjectPath->SetPath(FString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(Path, nullptr)))));
	}
}

void FSoftObjectPathImplementation::SoftObjectPath_ResetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		SoftObjectPath->Reset();
	}
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsValidImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsValid();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsNullImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsNull();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsAssetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsAsset();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_IsSubobjectImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->IsSubobject();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_EqualityImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto SoftObjectPathA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(A);

	const auto SoftObjectPathB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(B);

	if (SoftObjectPathA != nullptr && SoftObjectPathB)
	{
		return SoftObjectPathA->operator==(*SoftObjectPathB);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_InequalityImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto SoftObjectPathA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(A);

	const auto SoftObjectPathB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FSoftObjectPath>(B);

	if (SoftObjectPathA != nullptr && SoftObjectPathB)
	{
		return SoftObjectPathA->operator!=(*SoftObjectPathB);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->FixupForPIE();
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupForPIEInstanceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 PIEInstance)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

	if (SoftObjectPath != nullptr)
	{
		return SoftObjectPath->FixupForPIE(PIEInstance);
	}

	return false;
}

bool FSoftObjectPathImplementation::SoftObjectPath_FixupCoreRedirectsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto SoftObjectPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftObjectPath>(InGarbageCollectionHandle);

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
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle);

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
