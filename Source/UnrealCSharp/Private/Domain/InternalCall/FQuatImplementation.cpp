#include "Domain/InternalCall/FQuatImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterQuat
{
	FRegisterQuat()
	{
		TReflectionClassBuilder<FQuat>(NAMESPACE_LIBRARY)
			.Function("Add", FQuatImplementation::Quat_AddImplementation)
			.Function("Subtract", FQuatImplementation::Quat_SubtractImplementation)
			.Function("Equals", FQuatImplementation::Quat_EqualsImplementation)
			.Function("IsIdentity", FQuatImplementation::Quat_IsIdentityImplementation)
			.Function("Multiply", FQuatImplementation::Quat_MultiplyImplementation)
			.Function("MultiplyVector", FQuatImplementation::Quat_MultiplyVectorImplementation)
			.Function("MultiplyMatrix", FQuatImplementation::Quat_MultiplyMatrixImplementation)
			.Function("MultiplyScale", FQuatImplementation::Quat_MultiplyScaleImplementation)
			.Function("Divide", FQuatImplementation::Quat_DivideImplementation)
			.Function("Equality", FQuatImplementation::Quat_EqualityImplementation)
			.Function("Inequality", FQuatImplementation::Quat_InequalityImplementation)
			.Function("DotProduct", FQuatImplementation::Quat_DotProductImplementation)
			.Function("MakeFromEuler", FQuatImplementation::Quat_MakeFromEulerImplementation)
			.Function("Euler", FQuatImplementation::Quat_EulerImplementation)
			.Function("Normalize", FQuatImplementation::Quat_NormalizeImplementation)
			.Function("GetNormalized", FQuatImplementation::Quat_GetNormalizedImplementation)
			.Function("IsNormalized", FQuatImplementation::Quat_IsNormalizedImplementation)
			.Function("Size", FQuatImplementation::Quat_SizeImplementation)
			.Function("SizeSquared", FQuatImplementation::Quat_SizeSquaredImplementation)
			.Function("GetAngle", FQuatImplementation::Quat_GetAngleImplementation)
			.Function("ToAxisAndAngle", FQuatImplementation::Quat_ToAxisAndAngleImplementation)
			.Function("ToSwingTwist", FQuatImplementation::Quat_ToSwingTwistImplementation)
			.Function("GetTwistAngle", FQuatImplementation::Quat_GetTwistAngleImplementation)
			.Function("RotateVector", FQuatImplementation::Quat_RotateVectorImplementation)
			.Function("UnrotateVector", FQuatImplementation::Quat_UnrotateVectorImplementation)
			.Function("Log", FQuatImplementation::Quat_LogImplementation)
			.Function("Exp", FQuatImplementation::Quat_ExpImplementation)
			.Function("Inverse", FQuatImplementation::Quat_InverseImplementation)
			.Function("EnforceShortestArcWith", FQuatImplementation::Quat_EnforceShortestArcWithImplementation)
			.Function("GetAxisX", FQuatImplementation::Quat_GetAxisXImplementation)
			.Function("GetAxisY", FQuatImplementation::Quat_GetAxisYImplementation)
			.Function("GetAxisZ", FQuatImplementation::Quat_GetAxisZImplementation)
			.Function("GetForwardVector", FQuatImplementation::Quat_GetForwardVectorImplementation)
			.Function("GetRightVector", FQuatImplementation::Quat_GetRightVectorImplementation)
			.Function("GetUpVector", FQuatImplementation::Quat_GetUpVectorImplementation)
			.Function("Vector", FQuatImplementation::Quat_VectorImplementation)
			.Function("Rotator", FQuatImplementation::Quat_RotatorImplementation)
			.Function("GetRotationAxis", FQuatImplementation::Quat_GetRotationAxisImplementation)
			.Function("AngularDistance", FQuatImplementation::Quat_AngularDistanceImplementation)
			.Function("ContainsNaN", FQuatImplementation::Quat_ContainsNaNImplementation)
			.Function("ToString", FQuatImplementation::Quat_ToStringImplementation)
			.Function("InitFromString", FQuatImplementation::Quat_InitFromStringImplementation)
			.Function("FindBetween", FQuatImplementation::Quat_FindBetweenImplementation)
			.Function("FindBetweenNormals", FQuatImplementation::Quat_FindBetweenNormalsImplementation)
			.Function("FindBetweenVectors", FQuatImplementation::Quat_FindBetweenVectorsImplementation)
			.Function("Error", FQuatImplementation::Quat_ErrorImplementation)
			.Function("ErrorAutoNormalize", FQuatImplementation::Quat_ErrorAutoNormalizeImplementation)
			.Function("FastLerp", FQuatImplementation::Quat_FastLerpImplementation)
			.Function("FastBilerp", FQuatImplementation::Quat_FastBilerpImplementation)
			.Function("Slerp_NotNormalized", FQuatImplementation::Quat_Slerp_NotNormalizedImplementation)
			.Function("Slerp", FQuatImplementation::Quat_SlerpImplementation)
			.Function("SlerpFullPath_NotNormalized",
			          FQuatImplementation::Quat_SlerpFullPath_NotNormalizedImplementation)
			.Function("SlerpFullPath", FQuatImplementation::Quat_SlerpFullPathImplementation)
			.Function("Squad", FQuatImplementation::Quat_SquadImplementation)
			.Function("SquadFull", FQuatImplementation::Quat_SquadFullPathImplementation)
			.Function("CalcTangents", FQuatImplementation::Quat_CalcTangentsImplementation)
			.Register();
	}
};

static FRegisterQuat RegisterQuat;

void FQuatImplementation::Quat_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                 MonoObject** OutValue)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatA != nullptr && QuatB != nullptr && OutQuat != nullptr)
	{
		*OutQuat = QuatA->operator+(*QuatB);
	}
}

void FQuatImplementation::Quat_SubtractImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatA != nullptr && QuatB != nullptr && OutQuat != nullptr)
	{
		*OutQuat = QuatA->operator-(*QuatB);
	}
}

bool FQuatImplementation::Quat_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                    const LwcType Tolerance)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->Equals(*QuatB, Tolerance);
	}

	return false;
}

bool FQuatImplementation::Quat_IsIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const LwcType Tolerance)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	if (Quat != nullptr)
	{
		return Quat->IsIdentity(Tolerance);
	}

	return false;
}

void FQuatImplementation::Quat_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatA != nullptr && QuatB != nullptr && OutQuat != nullptr)
	{
		*OutQuat = QuatA->operator*(*QuatB);
	}
}

void FQuatImplementation::Quat_MultiplyVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* V, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->operator*(*Vector);
	}
}

void FQuatImplementation::Quat_MultiplyMatrixImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* M, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Quat != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Quat->operator*(*Matrix);
	}
}

void FQuatImplementation::Quat_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const LwcType Scale, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->operator*(Scale);
	}
}

void FQuatImplementation::Quat_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    const LwcType Scale, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->operator/(Scale);
	}
}

bool FQuatImplementation::Quat_IdenticalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       const MonoObject* Q, const uint32 PortFlags)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto QuatQ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	if (Quat != nullptr && QuatQ != nullptr)
	{
		return Quat->Identical(QuatQ, PortFlags);
	}

	return false;
}

bool FQuatImplementation::Quat_EqualityImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->operator==(*QuatB);
	}

	return false;
}

bool FQuatImplementation::Quat_InequalityImplementation(const FGarbageCollectionHandle A,
                                                        const FGarbageCollectionHandle B)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->operator!=(*QuatB);
	}

	return false;
}

FQuatImplementation::LwcType FQuatImplementation::Quat_DotProductImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->operator|(*QuatB);
	}

	return 0.f;
}

void FQuatImplementation::Quat_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Euler);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Vector != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::MakeFromEuler(*Vector);
	}
}

void FQuatImplementation::Quat_EulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->Euler();
	}
}

void FQuatImplementation::Quat_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       const LwcType Tolerance)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(
		InGarbageCollectionHandle))
	{
		Quat->Normalize(Tolerance);
	}
}

void FQuatImplementation::Quat_GetNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->GetNormalized(Tolerance);
	}
}

bool FQuatImplementation::Quat_IsNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(
		InGarbageCollectionHandle))
	{
		return Quat->IsNormalized();
	}

	return false;
}

FQuatImplementation::LwcType FQuatImplementation::Quat_SizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(
		InGarbageCollectionHandle))
	{
		return Quat->Size();
	}

	return 0.f;
}

FQuatImplementation::LwcType FQuatImplementation::Quat_SizeSquaredImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(
		InGarbageCollectionHandle))
	{
		return Quat->SizeSquared();
	}

	return 0.f;
}

FQuatImplementation::LwcType FQuatImplementation::Quat_GetAngleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(
		InGarbageCollectionHandle))
	{
		return Quat->GetAngle();
	}

	return 0.f;
}

void FQuatImplementation::Quat_ToAxisAndAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** Axis, LwcType& Angle)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		Quat->ToAxisAndAngle(*OutVector, Angle);
	}
}

void FQuatImplementation::Quat_ToSwingTwistImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const MonoObject* InTwistAxis, MonoObject** OutSwing,
                                                          MonoObject** OutTwist)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(InTwistAxis);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutSwing = NewMonoObject1;

	const auto OutSwingQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutTwist = NewMonoObject2;

	const auto OutTwistQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject2);

	if (Quat != nullptr && Vector != nullptr && OutSwingQuat != nullptr && OutTwistQuat != nullptr)
	{
		Quat->ToSwingTwist(*Vector, *OutSwingQuat, *OutTwistQuat);
	}
}

FQuatImplementation::LwcType FQuatImplementation::Quat_GetTwistAngleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* TwistAxis)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(TwistAxis);

	if (Quat != nullptr)
	{
		return Quat->GetTwistAngle(*Vector);
	}

	return 0.f;
}

void FQuatImplementation::Quat_RotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const MonoObject* V, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->RotateVector(*Vector);
	}
}

void FQuatImplementation::Quat_UnrotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* V, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->UnrotateVector(*Vector);
	}
}

void FQuatImplementation::Quat_LogImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                 MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Log();
	}
}

void FQuatImplementation::Quat_ExpImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                 MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Exp();
	}
}

void FQuatImplementation::Quat_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Inverse();
	}
}

void FQuatImplementation::Quat_EnforceShortestArcWithImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* OtherQuat)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto QuatOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(OtherQuat);

	if (Quat != nullptr && QuatOther != nullptr)
	{
		Quat->EnforceShortestArcWith(*QuatOther);
	}
}

void FQuatImplementation::Quat_GetAxisXImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisX();
	}
}

void FQuatImplementation::Quat_GetAxisYImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisY();
	}
}

void FQuatImplementation::Quat_GetAxisZImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisZ();
	}
}

void FQuatImplementation::Quat_GetForwardVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetForwardVector();
	}
}

void FQuatImplementation::Quat_GetRightVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetRightVector();
	}
}

void FQuatImplementation::Quat_GetUpVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetUpVector();
	}
}

void FQuatImplementation::Quat_VectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->Vector();
	}
}

void FQuatImplementation::Quat_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Quat != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Quat->Rotator();
	}
}

void FQuatImplementation::Quat_GetRotationAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetRotationAxis();
	}
}

FQuatImplementation::LwcType FQuatImplementation::Quat_AngularDistanceImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Q)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	const auto QuatQ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	if (Quat != nullptr && QuatQ != nullptr)
	{
		return Quat->AngularDistance(*QuatQ);
	}

	return 0.f;
}

bool FQuatImplementation::Quat_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	if (Quat != nullptr)
	{
		return Quat->ContainsNaN();
	}

	return false;
}

void FQuatImplementation::Quat_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	if (Quat != nullptr)
	{
		const auto ResultString = Quat->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FQuatImplementation::Quat_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject* InSourceString)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InGarbageCollectionHandle);

	if (Quat != nullptr && InSourceString != nullptr)
	{
		return Quat->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FQuatImplementation::Quat_FindBetweenImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
                                                         MonoObject** OutValue)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Vector1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Vector2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (VectorV1 != nullptr && VectorV2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::FindBetween(*VectorV1, *VectorV2);
	}
}

void FQuatImplementation::Quat_FindBetweenNormalsImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
                                                                MonoObject** OutValue)
{
	const auto Vector1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal1);

	const auto Vector2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Vector1 != nullptr && Vector2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::FindBetweenNormals(*Vector1, *Vector2);
	}
}

void FQuatImplementation::Quat_FindBetweenVectorsImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
                                                                MonoObject** OutValue)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Vector1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Vector2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (VectorV1 != nullptr && VectorV2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::FindBetweenVectors(*VectorV1, *VectorV2);
	}
}

FQuatImplementation::LwcType FQuatImplementation::Quat_ErrorImplementation(
	const FGarbageCollectionHandle Q1, const FGarbageCollectionHandle Q2)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q2);

	if (Quat1 != nullptr && Quat2 != nullptr)
	{
		return FQuat::Error(*Quat1, *Quat2);
	}

	return 0.f;
}

FQuatImplementation::LwcType FQuatImplementation::Quat_ErrorAutoNormalizeImplementation(
	const FGarbageCollectionHandle Q1, const FGarbageCollectionHandle Q2)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q2);

	if (Quat1 != nullptr && Quat2 != nullptr)
	{
		return FQuat::ErrorAutoNormalize(*Quat1, *Quat2);
	}

	return 0.f;
}

void FQuatImplementation::Quat_FastLerpImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B, const LwcType Alpha,
                                                      MonoObject** OutValue)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatA != nullptr && QuatB != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::FastLerp(*QuatA, *QuatB, Alpha);
	}
}

void FQuatImplementation::Quat_FastBilerpImplementation(const FGarbageCollectionHandle P00,
                                                        const FGarbageCollectionHandle P10,
                                                        const FGarbageCollectionHandle P01,
                                                        const FGarbageCollectionHandle P11, const LwcType FracX,
                                                        const LwcType FracY, MonoObject** OutValue)
{
	const auto QuatP00 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(P00);

	const auto QuatP10 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(P10);

	const auto QuatP01 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(P01);

	const auto QuatP11 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(P11);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatP00 != nullptr && QuatP10 != nullptr && QuatP01 != nullptr && QuatP11 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::FastBilerp(*QuatP00, *QuatP10, *QuatP01, *QuatP11, FracX, FracY);
	}
}

void FQuatImplementation::Quat_Slerp_NotNormalizedImplementation(const FGarbageCollectionHandle Quat1,
                                                                 const FGarbageCollectionHandle Quat2,
                                                                 const LwcType Slerp, MonoObject** OutValue)
{
	const auto QuatQ1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Quat1);

	const auto QuatQ2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Quat2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatQ1 != nullptr && QuatQ2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::Slerp_NotNormalized(*QuatQ1, *QuatQ2, Slerp);
	}
}

void FQuatImplementation::Quat_SlerpImplementation(const FGarbageCollectionHandle Quat1,
                                                   const FGarbageCollectionHandle Quat2, const LwcType Slerp,
                                                   MonoObject** OutValue)
{
	const auto QuatQ1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Quat1);

	const auto QuatQ2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Quat2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatQ1 != nullptr && QuatQ2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::Slerp(*QuatQ1, *QuatQ2, Slerp);
	}
}

void FQuatImplementation::Quat_SlerpFullPath_NotNormalizedImplementation(
	const FGarbageCollectionHandle quat1, const FGarbageCollectionHandle quat2, const LwcType Alpha,
	MonoObject** OutValue)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat1 != nullptr && Quat2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::SlerpFullPath_NotNormalized(*Quat1, *Quat2, Alpha);
	}
}

void FQuatImplementation::Quat_SlerpFullPathImplementation(const FGarbageCollectionHandle quat1,
                                                           const FGarbageCollectionHandle quat2, const LwcType Alpha,
                                                           MonoObject** OutValue)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat1 != nullptr && Quat2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::SlerpFullPath(*Quat1, *Quat2, Alpha);
	}
}

void FQuatImplementation::Quat_SquadImplementation(const FGarbageCollectionHandle quat1,
                                                   const FGarbageCollectionHandle tang1,
                                                   const FGarbageCollectionHandle quat2,
                                                   const FGarbageCollectionHandle tang2, const LwcType Alpha,
                                                   MonoObject** OutValue)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat1);

	const auto Tang1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(tang1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat2);

	const auto Tang2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(tang2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat1 != nullptr && Tang1 != nullptr && Quat2 != nullptr && Tang2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::Squad(*Quat1, *Tang1, *Quat2, *Tang2, Alpha);
	}
}

void FQuatImplementation::Quat_SquadFullPathImplementation(const FGarbageCollectionHandle quat1,
                                                           const FGarbageCollectionHandle tang1,
                                                           const FGarbageCollectionHandle quat2,
                                                           const FGarbageCollectionHandle tang2, const LwcType Alpha,
                                                           MonoObject** OutValue)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat1);

	const auto Tang1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(tang1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(quat2);

	const auto Tang2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(tang2);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat1 != nullptr && Tang1 != nullptr && Quat2 != nullptr && Tang2 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = FQuat::SquadFullPath(*Quat1, *Tang1, *Quat2, *Tang2, Alpha);
	}
}

void FQuatImplementation::Quat_CalcTangentsImplementation(const FGarbageCollectionHandle PrevP,
                                                          const FGarbageCollectionHandle P,
                                                          const FGarbageCollectionHandle NextP, const LwcType Tension,
                                                          MonoObject** OutValue)
{
	const auto QuatPrevP = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(PrevP);

	const auto QuatP = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(P);

	const auto QuatNextP = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NextP);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (QuatPrevP != nullptr && QuatP != nullptr && QuatNextP != nullptr && OutQuat != nullptr)
	{
		FQuat::CalcTangents(*QuatPrevP, *QuatP, *QuatNextP, Tension, *OutQuat);
	}
}
