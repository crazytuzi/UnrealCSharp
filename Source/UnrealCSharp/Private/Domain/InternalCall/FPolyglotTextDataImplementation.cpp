#include "Domain/InternalCall/FPolyglotTextDataImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Internationalization/PolyglotTextData.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPolyglotTextData
{
	FRegisterPolyglotTextData()
	{
		TReflectionClassBuilder<FPolyglotTextData>(NAMESPACE_LIBRARY)
			.Function("IsValid", FPolyglotTextDataImplementation::PolyglotTextData_IsValidImplementation)
			.Function("SetNativeCulture",
			          FPolyglotTextDataImplementation::PolyglotTextData_SetNativeCultureImplementation)
			.Function("GetNativeCulture",
			          FPolyglotTextDataImplementation::PolyglotTextData_GetNativeCultureImplementation)
			.Function("ResolveNativeCulture",
			          FPolyglotTextDataImplementation::PolyglotTextData_ResolveNativeCultureImplementation)
			.Function("SetIdentity", FPolyglotTextDataImplementation::PolyglotTextData_SetIdentityImplementation)
			.Function("GetIdentity", FPolyglotTextDataImplementation::PolyglotTextData_GetIdentityImplementation)
			.Function("GetNamespace", FPolyglotTextDataImplementation::PolyglotTextData_GetNamespaceImplementation)
			.Function("GetKey", FPolyglotTextDataImplementation::PolyglotTextData_GetKeyImplementation)
			.Function("SetNativeString",
			          FPolyglotTextDataImplementation::PolyglotTextData_SetNativeStringImplementation)
			.Function("GetNativeString",
			          FPolyglotTextDataImplementation::PolyglotTextData_GetNativeStringImplementation)
			.Function("AddLocalizedString",
			          FPolyglotTextDataImplementation::PolyglotTextData_AddLocalizedStringImplementation)
			.Function("RemoveLocalizedString",
			          FPolyglotTextDataImplementation::PolyglotTextData_RemoveLocalizedStringImplementation)
			.Function("GetLocalizedString",
			          FPolyglotTextDataImplementation::PolyglotTextData_GetLocalizedStringImplementation)
			.Function("ClearLocalizedStrings",
			          FPolyglotTextDataImplementation::PolyglotTextData_ClearLocalizedStringsImplementation)
			.Function("SetIsMinimalPatch",
			          FPolyglotTextDataImplementation::PolyglotTextData_SetIsMinimalPatchImplementation)
			.Function("GetIsMinimalPatch",
			          FPolyglotTextDataImplementation::PolyglotTextData_GetIsMinimalPatchImplementation)
			.Function("GetText", FPolyglotTextDataImplementation::PolyglotTextData_GetTextImplementation)
			.Register();
	}
};

static FRegisterPolyglotTextData RegisterPolyglotTextData;

bool FPolyglotTextDataImplementation::PolyglotTextData_IsValidImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutFailureReason)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	FText Text;

	const auto Result = PolyglotTextData->IsValid(&Text);

	const auto FoundMonoClass = TPropertyClass<FText, FText>::Get();

	auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
		TCHAR_TO_UTF8(*Text.ToString())));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		FoundMonoClass, 1, &NewMonoString);

	*OutFailureReason = NewMonoObject;

	return Result;
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetNativeCultureImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InNativeCulture)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetNativeCulture(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InNativeCulture, nullptr))));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNativeCultureImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNativeCulture();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_ResolveNativeCultureImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->ResolveNativeCulture();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetIdentityImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InNamespace, MonoObject* InKey)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetIdentity(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InNamespace, nullptr))),
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InKey, nullptr))));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetIdentityImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutNamespace, MonoObject** OutKey)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		FString StringOutNamespace, StringOutKey;

		PolyglotTextData->GetIdentity(StringOutNamespace, StringOutKey);

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString1 = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*StringOutNamespace)));

		auto NewMonoString2 = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*StringOutKey)));

		const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString1);

		const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString2);

		*OutNamespace = NewMonoObject1;

		*OutKey = NewMonoObject2;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNamespaceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNamespace();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetKeyImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetKey();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetNativeStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InNativeString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetNativeString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InNativeString, nullptr))));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNativeStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNativeString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_AddLocalizedStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture, MonoObject* InLocalizedString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->AddLocalizedString(
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InCulture, nullptr))),
			UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
					GetDomain()->Object_To_String(InLocalizedString, nullptr))));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_RemoveLocalizedStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->RemoveLocalizedString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InCulture, nullptr))));
	}
}

bool FPolyglotTextDataImplementation::PolyglotTextData_GetLocalizedStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture, MonoObject** OutLocalizedString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	FString String;

	const auto Result = PolyglotTextData->GetLocalizedString(
		UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InCulture, nullptr))), String);

	const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

	auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
		TCHAR_TO_UTF8(*String)));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		FoundMonoClass, 1, &NewMonoString);

	*OutLocalizedString = NewMonoObject;

	return Result;
}

void FPolyglotTextDataImplementation::PolyglotTextData_ClearLocalizedStringsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->ClearLocalizedStrings();
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetIsMinimalPatchImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const bool InIsMinimalPatch)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->IsMinimalPatch(InIsMinimalPatch);
	}
}

bool FPolyglotTextDataImplementation::PolyglotTextData_GetIsMinimalPatchImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		return PolyglotTextData->IsMinimalPatch();
	}

	return false;
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetTextImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPolyglotTextData>(InGarbageCollectionHandle);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetText();

		const auto FoundMonoClass = TPropertyClass<FText, FText>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
