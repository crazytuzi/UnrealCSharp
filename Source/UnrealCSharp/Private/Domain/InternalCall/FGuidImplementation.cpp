#include "Domain/InternalCall/FGuidImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterGuid
{
	FRegisterGuid()
	{
		TReflectionClassBuilder<FGuid>(NAMESPACE_LIBRARY)
			.Function("LessThan", FGuidImplementation::Guid_LessThanImplementation)
			.Function("GreaterThan", FGuidImplementation::Guid_GreaterThanImplementation)
			.Function("GetComponent", FGuidImplementation::Guid_GetComponentImplementation)
			.Function("SetComponent", FGuidImplementation::Guid_SetComponentImplementation)
			.Function("LexToString", FGuidImplementation::Guid_LexToStringImplementation)
			.Function("Invalidate", FGuidImplementation::Guid_InvalidateImplementation)
			.Function("IsValid", FGuidImplementation::Guid_IsValidImplementation)
			.Function("ToString", FGuidImplementation::Guid_ToStringImplementation)
			.Function("NewGuid", FGuidImplementation::Guid_NewGuidImplementation)
			.Function("Parse", FGuidImplementation::Guid_ParseImplementation)
			.Register();
	}
};

static FRegisterGuid RegisterGuid;

bool FGuidImplementation::Guid_LessThanImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator<(*GuidA, *GuidB);
	}

	return false;
}

bool FGuidImplementation::Guid_GreaterThanImplementation(const FGarbageCollectionHandle A,
                                                         const FGarbageCollectionHandle B)
{
	const auto GuidA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(A);

	const auto GuidB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(B);

	if (GuidA != nullptr && GuidB != nullptr)
	{
		return operator<(*GuidB, *GuidA);
	}

	return false;
}

uint32 FGuidImplementation::Guid_GetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 Index)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(InGarbageCollectionHandle);

	if (Guid != nullptr)
	{
		return Guid->operator[](Index);
	}

	return 0u;
}

void FGuidImplementation::Guid_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const int32 Index, const uint32 InValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(InGarbageCollectionHandle);

	if (Guid != nullptr)
	{
		Guid->operator[](Index) = InValue;
	}
}

void FGuidImplementation::Guid_LexToStringImplementation(const MonoObject* Value, MonoObject** OutValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(Value);

	if (Guid != nullptr)
	{
		const auto ResultString = LexToString(*Guid);

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FGuidImplementation::Guid_InvalidateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(InGarbageCollectionHandle);

	if (Guid != nullptr)
	{
		Guid->Invalidate();
	}
}

bool FGuidImplementation::Guid_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(InGarbageCollectionHandle);

	if (Guid != nullptr)
	{
		return Guid->IsValid();
	}

	return false;
}

void FGuidImplementation::Guid_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      MonoObject** OutValue)
{
	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(InGarbageCollectionHandle);

	if (Guid != nullptr)
	{
		const auto ResultString = Guid->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FGuidImplementation::Guid_NewGuidImplementation(MonoObject** OutValue)
{
	const auto FoundMonoClass = TPropertyClass<FGuid, FGuid>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutGuid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(NewMonoObject);

	if (OutGuid != nullptr)
	{
		*OutGuid = FGuid::NewGuid();
	}
}

bool FGuidImplementation::Guid_ParseImplementation(MonoObject* GuidString, MonoObject** OutGuid)
{
	const auto FoundMonoClass = TPropertyClass<FGuid, FGuid>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutGuid = NewMonoObject;

	const auto Guid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FGuid>(NewMonoObject);

	if (Guid != nullptr)
	{
		return FGuid::Parse(FString(UTF8_TO_TCHAR(
			                    FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::
				                    GetEnvironment().GetDomain()->Object_To_String(GuidString, nullptr)))), *Guid);
	}

	return false;
}
