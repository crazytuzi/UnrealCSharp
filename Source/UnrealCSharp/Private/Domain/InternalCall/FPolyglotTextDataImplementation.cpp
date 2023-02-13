#include "Domain/InternalCall/FPolyglotTextDataImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Internationalization/PolyglotTextData.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPolyglotTextData
{
	FRegisterPolyglotTextData()
	{
		TScriptStructBuilder<FPolyglotTextData>(NAMESPACE_LIBRARY)
			.Function("IsValid",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_IsValidImplementation))
			.Function("SetNativeCulture",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_SetNativeCultureImplementation))
			.Function("GetNativeCulture",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_GetNativeCultureImplementation))
			.Function("ResolveNativeCulture",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_ResolveNativeCultureImplementation))
			.Function("SetIdentity",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_SetIdentityImplementation))
			.Function("GetIdentity",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_GetIdentityImplementation))
			.Function("GetNamespace",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_GetNamespaceImplementation))
			.Function("GetKey",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_GetKeyImplementation))
			.Function("SetNativeString",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_SetNativeStringImplementation))
			.Function("GetNativeString",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_GetNativeStringImplementation))
			.Function("AddLocalizedString",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_AddLocalizedStringImplementation))
			.Function("RemoveLocalizedString",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_RemoveLocalizedStringImplementation))
			.Function("GetLocalizedString",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_GetLocalizedStringImplementation))
			.Function("ClearLocalizedStrings",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_ClearLocalizedStringsImplementation))
			.Function("SetIsMinimalPatch",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_SetIsMinimalPatchImplementation))
			.Function("GetIsMinimalPatch",
			          static_cast<void*>(
				          FPolyglotTextDataImplementation::PolyglotTextData_GetIsMinimalPatchImplementation))
			.Function("GetText",
			          static_cast<void*>(FPolyglotTextDataImplementation::PolyglotTextData_GetTextImplementation))
			.Register();
	}
};

static FRegisterPolyglotTextData RegisterPolyglotTextData;

bool FPolyglotTextDataImplementation::PolyglotTextData_IsValidImplementation(
	const MonoObject* InMonoObject, MonoObject** OutFailureReason)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	FText Text;

	const auto Result = PolyglotTextData->IsValid(&Text);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);

	auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
		TCHAR_TO_UTF8(*Text.ToString())));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
		FoundMonoClass, 1, &NewMonoString);

	*OutFailureReason = NewMonoObject;

	return Result;
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetNativeCultureImplementation(
	const MonoObject* InMonoObject, MonoObject* InNativeCulture)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetNativeCulture(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InNativeCulture, nullptr)));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNativeCultureImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNativeCulture();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_ResolveNativeCultureImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->ResolveNativeCulture();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetIdentityImplementation(
	const MonoObject* InMonoObject, MonoObject* InNamespace, MonoObject* InKey)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetIdentity(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InNamespace, nullptr)),
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InKey, nullptr)));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetIdentityImplementation(
	const MonoObject* InMonoObject, MonoObject** OutNamespace, MonoObject** OutKey)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		FString StringOutNamespace, StringOutKey;

		PolyglotTextData->GetIdentity(StringOutNamespace, StringOutKey);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString1 = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*StringOutNamespace)));

		auto NewMonoString2 = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*StringOutKey)));

		const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString1);

		const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString2);

		*OutNamespace = NewMonoObject1;

		*OutKey = NewMonoObject2;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNamespaceImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNamespace();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetKeyImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetKey();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetNativeStringImplementation(
	const MonoObject* InMonoObject, MonoObject* InNativeString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->SetNativeString(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InNativeString, nullptr)));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetNativeStringImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetNativeString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_AddLocalizedStringImplementation(
	const MonoObject* InMonoObject, MonoObject* InCulture, MonoObject* InLocalizedString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->AddLocalizedString(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InCulture, nullptr)),
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InLocalizedString, nullptr)));
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_RemoveLocalizedStringImplementation(
	const MonoObject* InMonoObject, MonoObject* InCulture)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->RemoveLocalizedString(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InCulture, nullptr)));
	}
}

bool FPolyglotTextDataImplementation::PolyglotTextData_GetLocalizedStringImplementation(
	const MonoObject* InMonoObject, MonoObject* InCulture, MonoObject** OutLocalizedString)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	FString String;

	const auto Result = PolyglotTextData->GetLocalizedString(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(InCulture, nullptr)), String);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

	auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
		TCHAR_TO_UTF8(*String)));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
		FoundMonoClass, 1, &NewMonoString);

	*OutLocalizedString = NewMonoObject;

	return Result;
}

void FPolyglotTextDataImplementation::PolyglotTextData_ClearLocalizedStringsImplementation(
	const MonoObject* InMonoObject)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->ClearLocalizedStrings();
	}
}

void FPolyglotTextDataImplementation::PolyglotTextData_SetIsMinimalPatchImplementation(
	const MonoObject* InMonoObject, const bool InIsMinimalPatch)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		PolyglotTextData->IsMinimalPatch(InIsMinimalPatch);
	}
}

bool FPolyglotTextDataImplementation::PolyglotTextData_GetIsMinimalPatchImplementation(const MonoObject* InMonoObject)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		return PolyglotTextData->IsMinimalPatch();
	}

	return false;
}

void FPolyglotTextDataImplementation::PolyglotTextData_GetTextImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto PolyglotTextData = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FPolyglotTextData>(InMonoObject);

	if (PolyglotTextData != nullptr)
	{
		const auto ResultString = PolyglotTextData->GetText();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
