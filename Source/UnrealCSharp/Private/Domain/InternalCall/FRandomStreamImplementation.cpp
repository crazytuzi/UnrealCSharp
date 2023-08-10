#include "Domain/InternalCall/FRandomStreamImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterRandomStream
{
	FRegisterRandomStream()
	{
		TReflectionClassBuilder<FRandomStream>(NAMESPACE_LIBRARY)
			.Function("Initialize", FRandomStreamImplementation::RandomStream_InitializeImplementation)
			.Function("InitializeName", FRandomStreamImplementation::RandomStream_InitializeNameImplementation)
			.Function("Reset", FRandomStreamImplementation::RandomStream_ResetImplementation)
			.Function("GetInitialSeed", FRandomStreamImplementation::RandomStream_GetInitialSeedImplementation)
			.Function("GenerateNewSeed", FRandomStreamImplementation::RandomStream_GenerateNewSeedImplementation)
			.Function("GetFraction", FRandomStreamImplementation::RandomStream_GetFractionImplementation)
			.Function("GetUnsignedInt", FRandomStreamImplementation::RandomStream_GetUnsignedIntImplementation)
			.Function("GetUnitVector", FRandomStreamImplementation::RandomStream_GetUnitVectorImplementation)
			.Function("GetCurrentSeed", FRandomStreamImplementation::RandomStream_GetCurrentSeedImplementation)
			.Function("FRand", FRandomStreamImplementation::RandomStream_FRandImplementation)
			.Function("RandHelper", FRandomStreamImplementation::RandomStream_RandHelperImplementation)
			.Function("RandRange", FRandomStreamImplementation::RandomStream_RandRangeImplementation)
			.Function("FRandRange", FRandomStreamImplementation::RandomStream_FRandRangeImplementation)
			.Function("VRand", FRandomStreamImplementation::RandomStream_VRandImplementation)
			.Function("VRandConeHalfAngle", FRandomStreamImplementation::RandomStream_VRandConeHalfAngleImplementation)
			.Function("VRandConeHorizontalAndVerticalHalfAngle",
			          FRandomStreamImplementation::RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation)
			.Register();
	}
};

static FRegisterRandomStream RegisterRandomStream;

void FRandomStreamImplementation::RandomStream_InitializeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 InSeed)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->Initialize(InSeed);
	}
}

void FRandomStreamImplementation::RandomStream_InitializeNameImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InName)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->Initialize(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InName, nullptr))));
	}
}

void FRandomStreamImplementation::RandomStream_ResetImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->Reset();
	}
}

int32 FRandomStreamImplementation::RandomStream_GetInitialSeedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetInitialSeed();
	}

	return 0;
}

void FRandomStreamImplementation::RandomStream_GenerateNewSeedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->GenerateNewSeed();
	}
}

float FRandomStreamImplementation::RandomStream_GetFractionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetFraction();
	}

	return 0.f;
}

uint32 FRandomStreamImplementation::RandomStream_GetUnsignedIntImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetUnsignedInt();
	}

	return 0u;
}

void FRandomStreamImplementation::RandomStream_GetUnitVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->GetUnitVector();
	}
}

int32 FRandomStreamImplementation::RandomStream_GetCurrentSeedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetCurrentSeed();
	}

	return 0;
}

float FRandomStreamImplementation::RandomStream_FRandImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->FRand();
	}

	return 0.f;
}

int32 FRandomStreamImplementation::RandomStream_RandHelperImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 A)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandHelper(A);
	}

	return 0;
}

int32 FRandomStreamImplementation::RandomStream_RandRangeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 Min, const int32 Max)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandRange(Min, Max);
	}

	return 0;
}

float FRandomStreamImplementation::RandomStream_FRandRangeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const float InMin, const float InMax)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandRange(InMin, InMax);
	}

	return 0.f;
}

void FRandomStreamImplementation::RandomStream_VRandImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRand();
	}
}

void FRandomStreamImplementation::RandomStream_VRandConeHalfAngleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Dir, const float ConeHalfAngleRad,
	MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Dir);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRandCone(*Vector, ConeHalfAngleRad);
	}
}

void FRandomStreamImplementation::RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Dir,
	const float HorizontalConeHalfAngleRad, const float VerticalConeHalfAngleRad, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Dir);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRandCone(*Vector, HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad);
	}
}

void FRandomStreamImplementation::RandomStream_ToStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InGarbageCollectionHandle);

	if (RandomStream != nullptr)
	{
		const auto ResultString = RandomStream->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
