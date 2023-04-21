#include "Domain/InternalCall/FRandomStreamImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterRandomStream
{
	FRegisterRandomStream()
	{
		TScriptStructBuilder<FRandomStream>(NAMESPACE_LIBRARY)
			.Function("Initialize",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_InitializeImplementation))
			.Function("InitializeName",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_InitializeNameImplementation))
			.Function("Reset", static_cast<void*>(FRandomStreamImplementation::RandomStream_ResetImplementation))
			.Function("GetInitialSeed",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GetInitialSeedImplementation))
			.Function("GenerateNewSeed",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GenerateNewSeedImplementation))
			.Function("GetFraction",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GetFractionImplementation))
			.Function("GetUnsignedInt",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GetUnsignedIntImplementation))
			.Function("GetUnitVector",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GetUnitVectorImplementation))
			.Function("GetCurrentSeed",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_GetCurrentSeedImplementation))
			.Function("FRand", static_cast<void*>(FRandomStreamImplementation::RandomStream_FRandImplementation))
			.Function("RandHelper",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_RandHelperImplementation))
			.Function("RandRange",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_RandRangeImplementation))
			.Function("FRandRange",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_FRandRangeImplementation))
			.Function("VRand", static_cast<void*>(FRandomStreamImplementation::RandomStream_VRandImplementation))
			.Function("VRandConeHalfAngle",
			          static_cast<void*>(FRandomStreamImplementation::RandomStream_VRandConeHalfAngleImplementation))
			.Function("VRandConeHorizontalAndVerticalHalfAngle",
			          static_cast<void*>(
				          FRandomStreamImplementation::RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation))
			.Register();
	}
};

static FRegisterRandomStream RegisterRandomStream;

void FRandomStreamImplementation::RandomStream_InitializeImplementation(const MonoObject* InMonoObject,
                                                                        const int32 InSeed)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->Initialize(InSeed);
	}
}

void FRandomStreamImplementation::RandomStream_InitializeNameImplementation(
	const MonoObject* InMonoObject, MonoObject* InName)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->Initialize(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InName, nullptr))));
	}
}

void FRandomStreamImplementation::RandomStream_ResetImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->Reset();
	}
}

int32 FRandomStreamImplementation::RandomStream_GetInitialSeedImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetInitialSeed();
	}

	return 0;
}

void FRandomStreamImplementation::RandomStream_GenerateNewSeedImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->GenerateNewSeed();
	}
}

float FRandomStreamImplementation::RandomStream_GetFractionImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetFraction();
	}

	return 0.f;
}

uint32 FRandomStreamImplementation::RandomStream_GetUnsignedIntImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetUnsignedInt();
	}

	return 0u;
}

void FRandomStreamImplementation::RandomStream_GetUnitVectorImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->GetUnitVector();
	}
}

int32 FRandomStreamImplementation::RandomStream_GetCurrentSeedImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->GetCurrentSeed();
	}

	return 0;
}

float FRandomStreamImplementation::RandomStream_FRandImplementation(const MonoObject* InMonoObject)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->FRand();
	}

	return 0.f;
}

int32 FRandomStreamImplementation::RandomStream_RandHelperImplementation(const MonoObject* InMonoObject, const int32 A)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandHelper(A);
	}

	return 0;
}

int32 FRandomStreamImplementation::RandomStream_RandRangeImplementation(const MonoObject* InMonoObject, const int32 Min,
                                                                        const int32 Max)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandRange(Min, Max);
	}

	return 0;
}

float FRandomStreamImplementation::RandomStream_FRandRangeImplementation(
	const MonoObject* InMonoObject, const float InMin, const float InMax)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		return RandomStream->RandRange(InMin, InMax);
	}

	return 0.f;
}

void FRandomStreamImplementation::RandomStream_VRandImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRand();
	}
}

void FRandomStreamImplementation::RandomStream_VRandConeHalfAngleImplementation(
	const MonoObject* InMonoObject, const MonoObject* Dir, const float ConeHalfAngleRad, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Dir);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRandCone(*Vector, ConeHalfAngleRad);
	}
}

void FRandomStreamImplementation::RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
	const MonoObject* InMonoObject, const MonoObject* Dir, const float HorizontalConeHalfAngleRad,
	const float VerticalConeHalfAngleRad, MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Dir);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (RandomStream != nullptr && OutVector != nullptr)
	{
		*OutVector = RandomStream->VRandCone(*Vector, HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad);
	}
}

void FRandomStreamImplementation::RandomStream_ToStringImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject** OutValue)
{
	const auto RandomStream = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FRandomStream>(InMonoObject);

	if (RandomStream != nullptr)
	{
		const auto ResultString = RandomStream->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
