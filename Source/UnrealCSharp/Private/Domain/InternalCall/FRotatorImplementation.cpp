#include "Domain/InternalCall/FRotatorImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterRotator
{
	FRegisterRotator()
	{
		TReflectionClassBuilder<FRotator>(NAMESPACE_LIBRARY)
			.Function("Add", FRotatorImplementation::Rotator_AddImplementation)
			.Function("Subtract", FRotatorImplementation::Rotator_SubtractImplementation)
			.Function("Multiply", FRotatorImplementation::Rotator_MultiplyImplementation)
			.Function("Equals", FRotatorImplementation::Rotator_EqualsImplementation)
			.Function("AddDelta", FRotatorImplementation::Rotator_AddDeltaImplementation)
			.Function("GetInverse", FRotatorImplementation::Rotator_GetInverseImplementation)
			.Function("GridSnap", FRotatorImplementation::Rotator_GridSnapImplementation)
			.Function("Vector", FRotatorImplementation::Rotator_VectorImplementation)
			.Function("Quaternion", FRotatorImplementation::Rotator_QuaternionImplementation)
			.Function("Euler", FRotatorImplementation::Rotator_EulerImplementation)
			.Function("RotateVector", FRotatorImplementation::Rotator_RotateVectorImplementation)
			.Function("UnrotateVector", FRotatorImplementation::Rotator_UnrotateVectorImplementation)
			.Function("Clamp", FRotatorImplementation::Rotator_ClampImplementation)
			.Function("GetNormalized", FRotatorImplementation::Rotator_GetNormalizedImplementation)
			.Function("GetDenormalized", FRotatorImplementation::Rotator_GetDenormalizedImplementation)
			.Function("Normalize", FRotatorImplementation::Rotator_NormalizeImplementation)
			.Function("GetWindingAndRemainder", FRotatorImplementation::Rotator_GetWindingAndRemainderImplementation)
			.Function("GetManhattanDistance", FRotatorImplementation::Rotator_GetManhattanDistanceImplementation)
			.Function("GetEquivalentRotator", FRotatorImplementation::Rotator_GetEquivalentRotatorImplementation)
			.Function("SetClosestTo", FRotatorImplementation::Rotator_SetClosestToMeImplementation)
			.Function("ToString", FRotatorImplementation::Rotator_ToStringImplementation)
			.Function("ToCompactString", FRotatorImplementation::Rotator_ToCompactStringImplementation)
			.Function("InitFromString", FRotatorImplementation::Rotator_InitFromStringImplementation)
			.Function("ContainsNaN", FRotatorImplementation::Rotator_ContainsNaNImplementation)
			.Function("ClampAxis", FRotatorImplementation::Rotator_ClampAxisImplementation)
			.Function("NormalizeAxis", FRotatorImplementation::Rotator_NormalizeAxisImplementation)
			.Function("CompressAxisToByte", FRotatorImplementation::Rotator_CompressAxisToByteImplementation)
			.Function("DecompressAxisFromByte", FRotatorImplementation::Rotator_DecompressAxisFromByteImplementation)
			.Function("CompressAxisToShort", FRotatorImplementation::Rotator_CompressAxisToShortImplementation)
			.Function("DecompressAxisFromShort", FRotatorImplementation::Rotator_DecompressAxisFromShortImplementation)
			.Function("MakeFromEuler", FRotatorImplementation::Rotator_MakeFromEulerImplementation)
			.Register();
	}
};

static FRegisterRotator RegisterRotator;

void FRotatorImplementation::Rotator_AddImplementation(const FGarbageCollectionHandle A,
                                                       const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (RotatorA != nullptr && RotatorB != nullptr && OutRotator != nullptr)
	{
		*OutRotator = RotatorA->operator+(*RotatorB);
	}
}

void FRotatorImplementation::Rotator_SubtractImplementation(const FGarbageCollectionHandle A,
                                                            const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (RotatorA != nullptr && RotatorB != nullptr && OutRotator != nullptr)
	{
		*OutRotator = RotatorA->operator-(*RotatorB);
	}
}

void FRotatorImplementation::Rotator_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const LwcType Scale, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->operator*(Scale);
	}
}

bool FRotatorImplementation::Rotator_IsNearlyZeroImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle))
	{
		return Rotator->IsNearlyZero(Tolerance);
	}

	return false;
}

bool FRotatorImplementation::Rotator_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle))
	{
		return Rotator->IsZero();
	}

	return false;
}

bool FRotatorImplementation::Rotator_EqualsImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->Equals(*RotatorB, Tolerance);
	}

	return false;
}

void FRotatorImplementation::Rotator_AddDeltaImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const LwcType DeltaPitch, const LwcType DeltaYaw,
                                                            const LwcType DeltaRoll, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->Add(DeltaPitch, DeltaYaw, DeltaRoll);
	}
}

void FRotatorImplementation::Rotator_GetInverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetInverse();
	}
}

void FRotatorImplementation::Rotator_GridSnapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* RotGrid, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto RotatorRotGrid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(RotGrid);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && RotatorRotGrid != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GridSnap(*RotatorRotGrid);
	}
}

void FRotatorImplementation::Rotator_VectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->Vector();
	}
}

void FRotatorImplementation::Rotator_QuaternionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Rotator != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Rotator->Quaternion();
	}
}

void FRotatorImplementation::Rotator_EulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->Euler();
	}
}

void FRotatorImplementation::Rotator_RotateVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->RotateVector(*Vector);
	}
}

void FRotatorImplementation::Rotator_UnrotateVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->UnrotateVector(*Vector);
	}
}

void FRotatorImplementation::Rotator_ClampImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->Clamp();
	}
}

void FRotatorImplementation::Rotator_GetNormalizedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetNormalized();
	}
}

void FRotatorImplementation::Rotator_GetDenormalizedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetDenormalized();
	}
}

void FRotatorImplementation::Rotator_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle))
	{
		Rotator->Normalize();
	}
}

void FRotatorImplementation::Rotator_GetWindingAndRemainderImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** Winding, MonoObject** Remainder)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Winding = NewMonoObject1;

	const auto OutWindingRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Remainder = NewMonoObject2;

	const auto OutRemainderRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		NewMonoObject2);

	if (Rotator != nullptr && OutWindingRotator != nullptr && OutRemainderRotator != nullptr)
	{
		Rotator->GetWindingAndRemainder(*OutWindingRotator, *OutRemainderRotator);
	}
}

FRotatorImplementation::LwcType FRotatorImplementation::Rotator_GetManhattanDistanceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Rotator)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(Rotator);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->GetManhattanDistance(*RotatorB);
	}

	return 0.f;
}

void FRotatorImplementation::Rotator_GetEquivalentRotatorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetEquivalentRotator();
	}
}

void FRotatorImplementation::Rotator_SetClosestToMeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		Rotator->SetClosestToMe(*OutRotator);
	}
}

void FRotatorImplementation::Rotator_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	if (Rotator != nullptr)
	{
		const auto ResultString = Rotator->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FRotatorImplementation::Rotator_ToCompactStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	if (Rotator != nullptr)
	{
		const auto ResultString = Rotator->ToCompactString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FRotatorImplementation::Rotator_InitFromStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InSourceString)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	if (Rotator != nullptr && InSourceString != nullptr)
	{
		return Rotator->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

bool FRotatorImplementation::Rotator_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(
		InGarbageCollectionHandle);

	if (Rotator != nullptr)
	{
		return Rotator->ContainsNaN();
	}

	return false;
}

FRotatorImplementation::LwcType FRotatorImplementation::Rotator_ClampAxisImplementation(const LwcType Angle)
{
	return FRotator::ClampAxis(Angle);
}

FRotatorImplementation::LwcType FRotatorImplementation::Rotator_NormalizeAxisImplementation(const LwcType Angle)
{
	return FRotator::NormalizeAxis(Angle);
}

uint8 FRotatorImplementation::Rotator_CompressAxisToByteImplementation(const LwcType Angle)
{
	return FRotator::CompressAxisToByte(Angle);
}

FRotatorImplementation::LwcType FRotatorImplementation::Rotator_DecompressAxisFromByteImplementation(const uint8 Angle)
{
	return FRotator::DecompressAxisFromByte(Angle);
}

uint16 FRotatorImplementation::Rotator_CompressAxisToShortImplementation(const LwcType Angle)
{
	return FRotator::CompressAxisToShort(Angle);
}

FRotatorImplementation::LwcType FRotatorImplementation::Rotator_DecompressAxisFromShortImplementation(
	const uint16 Angle)
{
	return FRotator::DecompressAxisFromShort(Angle);
}

void FRotatorImplementation::Rotator_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Euler);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector != nullptr && OutRotator != nullptr)
	{
		*OutRotator = FRotator::MakeFromEuler(*Vector);
	}
}
