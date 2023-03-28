#include "Domain/InternalCall/FGuidImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterGuid
{
	FRegisterGuid()
	{
		TScriptStructBuilder<FGuid>(NAMESPACE_LIBRARY)
			.Function("Equality", static_cast<void*>(FGuidImplementation::Guid_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FGuidImplementation::Guid_InequalityImplementation))
			.Function("LessThan", static_cast<void*>(FGuidImplementation::Guid_LessThanImplementation))
			.Function("GreaterThan", static_cast<void*>(FGuidImplementation::Guid_GreaterThanImplementation))
			.Function("GetComponent", static_cast<void*>(FGuidImplementation::Guid_GetComponentImplementation))
			.Function("SetComponent", static_cast<void*>(FGuidImplementation::Guid_SetComponentImplementation))
			.Function("LexToString", static_cast<void*>(FGuidImplementation::Guid_LexToStringImplementation))
			.Function("Invalidate", static_cast<void*>(FGuidImplementation::Guid_InvalidateImplementation))
			.Function("IsValid", static_cast<void*>(FGuidImplementation::Guid_IsValidImplementation))
			.Function("ToString", static_cast<void*>(FGuidImplementation::Guid_ToStringImplementation))
			.Function("NewGuid", static_cast<void*>(FGuidImplementation::Guid_NewGuidImplementation))
			.Function("Parse", static_cast<void*>(FGuidImplementation::Guid_ParseImplementation))
			.Register();
	}
};

static FRegisterGuid RegisterGuid;

bool FGuidImplementation::Guid_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator==(*GuidA, *GuidB);
	}

	return false;
}

bool FGuidImplementation::Guid_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator!=(*GuidA, *GuidB);
	}

	return false;
}

bool FGuidImplementation::Guid_LessThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator<(*GuidA, *GuidB);
	}

	return false;
}

bool FGuidImplementation::Guid_GreaterThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator<(*GuidB, *GuidA);
	}

	return false;
}

uint32 FGuidImplementation::Guid_GetComponentImplementation(const MonoObject* InMonoObject, const int32 Index)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		return Guid->operator[](Index);
	}

	return 0u;
}

void FGuidImplementation::Guid_SetComponentImplementation(const MonoObject* InMonoObject, const int32 Index,
                                                          const uint32 InValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		Guid->operator[](Index) = InValue;
	}
}

void FGuidImplementation::Guid_LexToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		const auto ResultString = LexToString(*Guid);

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FGuidImplementation::Guid_InvalidateImplementation(const MonoObject* InMonoObject)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		Guid->Invalidate();
	}
}

bool FGuidImplementation::Guid_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		return Guid->IsValid();
	}

	return false;
}

void FGuidImplementation::Guid_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(InMonoObject);

	if (Guid != nullptr)
	{
		const auto ResultString = Guid->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FGuidImplementation::Guid_NewGuidImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FGuid)),
		CLASS_SCRIPT_STRUCT_NAME(FGuid));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutGuid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(NewMonoObject);

	if (OutGuid != nullptr)
	{
		*OutGuid = FGuid::NewGuid();
	}
}

bool FGuidImplementation::Guid_ParseImplementation(MonoObject* GuidString, MonoObject** OutGuid)
{
	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FGuid)),
		CLASS_SCRIPT_STRUCT_NAME(FGuid));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutGuid = NewMonoObject;

	const auto Guid = FCSharpEnvironment::GetEnvironment()->GetAddress<UScriptStruct, FGuid>(NewMonoObject);

	if (Guid != nullptr)
	{
		return FGuid::Parse(FString(UTF8_TO_TCHAR(
			                    FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(FCSharpEnvironment::
				                    GetEnvironment()->GetDomain()->Object_To_String(GuidString, nullptr)))), *Guid);
	}

	return false;
}
