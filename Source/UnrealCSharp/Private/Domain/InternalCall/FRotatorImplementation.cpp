#include "Domain/InternalCall/FRotatorImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterRotator
{
	FRegisterRotator()
	{
		TScriptStructBuilder<FRotator>(NAMESPACE_LIBRARY)
			.Function("Add", static_cast<void*>(FRotatorImplementation::Rotator_AddImplementation))
			.Function("Subtract", static_cast<void*>(FRotatorImplementation::Rotator_SubtractImplementation))
			.Function("Multiply", static_cast<void*>(FRotatorImplementation::Rotator_MultiplyImplementation))
			.Function("Equality", static_cast<void*>(FRotatorImplementation::Rotator_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FRotatorImplementation::Rotator_InequalityImplementation))
			.Function("Equals", static_cast<void*>(FRotatorImplementation::Rotator_EqualsImplementation))
			.Function("AddDelta", static_cast<void*>(FRotatorImplementation::Rotator_AddDeltaImplementation))
			.Function("GetInverse", static_cast<void*>(FRotatorImplementation::Rotator_GetInverseImplementation))
			.Function("GridSnap", static_cast<void*>(FRotatorImplementation::Rotator_GridSnapImplementation))
			.Function("Vector", static_cast<void*>(FRotatorImplementation::Rotator_VectorImplementation))
			.Function("Quaternion", static_cast<void*>(FRotatorImplementation::Rotator_QuaternionImplementation))
			.Function("Euler", static_cast<void*>(FRotatorImplementation::Rotator_EulerImplementation))
			.Function("RotateVector", static_cast<void*>(FRotatorImplementation::Rotator_RotateVectorImplementation))
			.Function("UnrotateVector",
			          static_cast<void*>(FRotatorImplementation::Rotator_UnrotateVectorImplementation))
			.Function("Clamp", static_cast<void*>(FRotatorImplementation::Rotator_ClampImplementation))
			.Function("GetNormalized", static_cast<void*>(FRotatorImplementation::Rotator_GetNormalizedImplementation))
			.Function("GetDenormalized",
			          static_cast<void*>(FRotatorImplementation::Rotator_GetDenormalizedImplementation))
			.Function("Normalize", static_cast<void*>(FRotatorImplementation::Rotator_NormalizeImplementation))
			.Function("GetWindingAndRemainder",
			          static_cast<void*>(FRotatorImplementation::Rotator_GetWindingAndRemainderImplementation))
			.Function("GetManhattanDistance",
			          static_cast<void*>(FRotatorImplementation::Rotator_GetManhattanDistanceImplementation))
			.Function("GetEquivalentRotator",
			          static_cast<void*>(FRotatorImplementation::Rotator_GetEquivalentRotatorImplementation))
			.Function("SetClosestTo", static_cast<void*>(FRotatorImplementation::Rotator_SetClosestToMeImplementation))
			.Function("ToString", static_cast<void*>(FRotatorImplementation::Rotator_ToStringImplementation))
			.Function("ToCompactString",
			          static_cast<void*>(FRotatorImplementation::Rotator_ToCompactStringImplementation))
			.Function("InitFromString",
			          static_cast<void*>(FRotatorImplementation::Rotator_InitFromStringImplementation))
			.Function("ContainsNaN", static_cast<void*>(FRotatorImplementation::Rotator_ContainsNaNImplementation))
			.Function("ClampAxis", static_cast<void*>(FRotatorImplementation::Rotator_ClampAxisImplementation))
			.Function("NormalizeAxis", static_cast<void*>(FRotatorImplementation::Rotator_NormalizeAxisImplementation))
			.Function("CompressAxisToByte",
			          static_cast<void*>(FRotatorImplementation::Rotator_CompressAxisToByteImplementation))
			.Function("DecompressAxisFromByte",
			          static_cast<void*>(FRotatorImplementation::Rotator_DecompressAxisFromByteImplementation))
			.Function("CompressAxisToShort",
			          static_cast<void*>(FRotatorImplementation::Rotator_CompressAxisToShortImplementation))
			.Function("DecompressAxisFromShort",
			          static_cast<void*>(FRotatorImplementation::Rotator_DecompressAxisFromShortImplementation))
			.Function("MakeFromEuler", static_cast<void*>(FRotatorImplementation::Rotator_MakeFromEulerImplementation))
			.Register();
	}
};

static FRegisterRotator RegisterRotator;

void FRotatorImplementation::Rotator_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (RotatorA != nullptr && RotatorB != nullptr && OutRotator != nullptr)
	{
		*OutRotator = RotatorA->operator+(*RotatorB);
	}
}

void FRotatorImplementation::Rotator_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                            MonoObject** OutValue)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (RotatorA != nullptr && RotatorB != nullptr && OutRotator != nullptr)
	{
		*OutRotator = RotatorA->operator-(*RotatorB);
	}
}

void FRotatorImplementation::Rotator_MultiplyImplementation(const MonoObject* InMonoObject, const float Scale,
                                                            MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->operator*(Scale);
	}
}

bool FRotatorImplementation::Rotator_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->operator==(*RotatorB);
	}

	return false;
}

bool FRotatorImplementation::Rotator_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->operator!=(*RotatorB);
	}

	return false;
}

bool FRotatorImplementation::Rotator_IsNearlyZeroImplementation(const MonoObject* InMonoObject, const float Tolerance)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject))
	{
		return Rotator->IsNearlyZero(Tolerance);
	}

	return false;
}

bool FRotatorImplementation::Rotator_IsZeroImplementation(const MonoObject* InMonoObject)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject))
	{
		return Rotator->IsZero();
	}

	return false;
}

bool FRotatorImplementation::Rotator_EqualsImplementation(const MonoObject* A, const MonoObject* B,
                                                          const float Tolerance)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(A);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(B);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->Equals(*RotatorB, Tolerance);
	}

	return false;
}

void FRotatorImplementation::Rotator_AddDeltaImplementation(const MonoObject* InMonoObject, const float DeltaPitch,
                                                            const float DeltaYaw, const float DeltaRoll,
                                                            MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->Add(DeltaPitch, DeltaYaw, DeltaRoll);
	}
}

void FRotatorImplementation::Rotator_GetInverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetInverse();
	}
}

void FRotatorImplementation::Rotator_GridSnapImplementation(const MonoObject* InMonoObject, const MonoObject* RotGrid,
                                                            MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto RotatorRotGrid = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(RotGrid);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && RotatorRotGrid != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GridSnap(*RotatorRotGrid);
	}
}

void FRotatorImplementation::Rotator_VectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->Vector();
	}
}

void FRotatorImplementation::Rotator_QuaternionImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Rotator != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Rotator->Quaternion();
	}
}

void FRotatorImplementation::Rotator_EulerImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->Euler();
	}
}

void FRotatorImplementation::Rotator_RotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                                MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->RotateVector(*Vector);
	}
}

void FRotatorImplementation::Rotator_UnrotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                                  MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Rotator != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Rotator->UnrotateVector(*Vector);
	}
}

void FRotatorImplementation::Rotator_ClampImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->Clamp();
	}
}

void FRotatorImplementation::Rotator_GetNormalizedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetNormalized();
	}
}

void FRotatorImplementation::Rotator_GetDenormalizedImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetDenormalized();
	}
}

void FRotatorImplementation::Rotator_NormalizeImplementation(const MonoObject* InMonoObject)
{
	if (const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject))
	{
		Rotator->Normalize();
	}
}

void FRotatorImplementation::Rotator_GetWindingAndRemainderImplementation(
	const MonoObject* InMonoObject, MonoObject** Winding, MonoObject** Remainder)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

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

float FRotatorImplementation::Rotator_GetManhattanDistanceImplementation(
	const MonoObject* InMonoObject, const MonoObject* Rotator)
{
	const auto RotatorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto RotatorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(Rotator);

	if (RotatorA != nullptr && RotatorB != nullptr)
	{
		return RotatorA->GetManhattanDistance(*RotatorB);
	}

	return 0.f;
}

void FRotatorImplementation::Rotator_GetEquivalentRotatorImplementation(const MonoObject* InMonoObject,
                                                                        MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Rotator->GetEquivalentRotator();
	}
}

void FRotatorImplementation::Rotator_SetClosestToMeImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Rotator != nullptr && OutRotator != nullptr)
	{
		Rotator->SetClosestToMe(*OutRotator);
	}
}

void FRotatorImplementation::Rotator_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	if (Rotator != nullptr)
	{
		const auto ResultString = Rotator->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FRotatorImplementation::Rotator_ToCompactStringImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	if (Rotator != nullptr)
	{
		const auto ResultString = Rotator->ToCompactString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FRotatorImplementation::Rotator_InitFromStringImplementation(const MonoObject* InMonoObject,
                                                                  MonoObject* InSourceString)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	if (Rotator != nullptr && InSourceString != nullptr)
	{
		return Rotator->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

bool FRotatorImplementation::Rotator_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Rotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(InMonoObject);

	if (Rotator != nullptr)
	{
		return Rotator->ContainsNaN();
	}

	return false;
}

float FRotatorImplementation::Rotator_ClampAxisImplementation(const float Angle)
{
	return FRotator::ClampAxis(Angle);
}

float FRotatorImplementation::Rotator_NormalizeAxisImplementation(const float Angle)
{
	return FRotator::NormalizeAxis(Angle);
}

uint8 FRotatorImplementation::Rotator_CompressAxisToByteImplementation(const float Angle)
{
	return FRotator::CompressAxisToByte(Angle);
}

float FRotatorImplementation::Rotator_DecompressAxisFromByteImplementation(const uint8 Angle)
{
	return FRotator::DecompressAxisFromByte(Angle);
}

uint16 FRotatorImplementation::Rotator_CompressAxisToShortImplementation(const float Angle)
{
	return FRotator::CompressAxisToShort(Angle);
}

float FRotatorImplementation::Rotator_DecompressAxisFromShortImplementation(const uint16 Angle)
{
	return FRotator::DecompressAxisFromShort(Angle);
}

void FRotatorImplementation::Rotator_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Euler);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector != nullptr && OutRotator != nullptr)
	{
		*OutRotator = FRotator::MakeFromEuler(*Vector);
	}
}
