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
			.Function("Add", static_cast<void*>(FQuatImplementation::Quat_AddImplementation))
			.Function("Subtract", static_cast<void*>(FQuatImplementation::Quat_SubtractImplementation))
			.Function("Equals", static_cast<void*>(FQuatImplementation::Quat_EqualsImplementation))
			.Function("IsIdentity", static_cast<void*>(FQuatImplementation::Quat_IsIdentityImplementation))
			.Function("Multiply", static_cast<void*>(FQuatImplementation::Quat_MultiplyImplementation))
			.Function("MultiplyVector", static_cast<void*>(FQuatImplementation::Quat_MultiplyVectorImplementation))
			.Function("MultiplyMatrix", static_cast<void*>(FQuatImplementation::Quat_MultiplyMatrixImplementation))
			.Function("MultiplyScale", static_cast<void*>(FQuatImplementation::Quat_MultiplyScaleImplementation))
			.Function("Divide", static_cast<void*>(FQuatImplementation::Quat_DivideImplementation))
			.Function("Equality", static_cast<void*>(FQuatImplementation::Quat_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FQuatImplementation::Quat_InequalityImplementation))
			.Function("DotProduct", static_cast<void*>(FQuatImplementation::Quat_DotProductImplementation))
			.Function("MakeFromEuler", static_cast<void*>(FQuatImplementation::Quat_MakeFromEulerImplementation))
			.Function("Euler", static_cast<void*>(FQuatImplementation::Quat_EulerImplementation))
			.Function("Normalize", static_cast<void*>(FQuatImplementation::Quat_NormalizeImplementation))
			.Function("GetNormalized", static_cast<void*>(FQuatImplementation::Quat_GetNormalizedImplementation))
			.Function("IsNormalized", static_cast<void*>(FQuatImplementation::Quat_IsNormalizedImplementation))
			.Function("Size", static_cast<void*>(FQuatImplementation::Quat_SizeImplementation))
			.Function("SizeSquared", static_cast<void*>(FQuatImplementation::Quat_SizeSquaredImplementation))
			.Function("GetAngle", static_cast<void*>(FQuatImplementation::Quat_GetAngleImplementation))
			.Function("ToAxisAndAngle", static_cast<void*>(FQuatImplementation::Quat_ToAxisAndAngleImplementation))
			.Function("ToSwingTwist", static_cast<void*>(FQuatImplementation::Quat_ToSwingTwistImplementation))
			.Function("GetTwistAngle", static_cast<void*>(FQuatImplementation::Quat_GetTwistAngleImplementation))
			.Function("RotateVector", static_cast<void*>(FQuatImplementation::Quat_RotateVectorImplementation))
			.Function("UnrotateVector", static_cast<void*>(FQuatImplementation::Quat_UnrotateVectorImplementation))
			.Function("Log", static_cast<void*>(FQuatImplementation::Quat_LogImplementation))
			.Function("Exp", static_cast<void*>(FQuatImplementation::Quat_ExpImplementation))
			.Function("Inverse", static_cast<void*>(FQuatImplementation::Quat_InverseImplementation))
			.Function("EnforceShortestArcWith",
			          static_cast<void*>(FQuatImplementation::Quat_EnforceShortestArcWithImplementation))
			.Function("GetAxisX", static_cast<void*>(FQuatImplementation::Quat_GetAxisXImplementation))
			.Function("GetAxisY", static_cast<void*>(FQuatImplementation::Quat_GetAxisYImplementation))
			.Function("GetAxisZ", static_cast<void*>(FQuatImplementation::Quat_GetAxisZImplementation))
			.Function("GetForwardVector", static_cast<void*>(FQuatImplementation::Quat_GetForwardVectorImplementation))
			.Function("GetRightVector", static_cast<void*>(FQuatImplementation::Quat_GetRightVectorImplementation))
			.Function("GetUpVector", static_cast<void*>(FQuatImplementation::Quat_GetUpVectorImplementation))
			.Function("Vector", static_cast<void*>(FQuatImplementation::Quat_VectorImplementation))
			.Function("Rotator", static_cast<void*>(FQuatImplementation::Quat_RotatorImplementation))
			.Function("GetRotationAxis", static_cast<void*>(FQuatImplementation::Quat_GetRotationAxisImplementation))
			.Function("AngularDistance", static_cast<void*>(FQuatImplementation::Quat_AngularDistanceImplementation))
			.Function("ContainsNaN", static_cast<void*>(FQuatImplementation::Quat_ContainsNaNImplementation))
			.Function("ToString", static_cast<void*>(FQuatImplementation::Quat_ToStringImplementation))
			.Function("InitFromString", static_cast<void*>(FQuatImplementation::Quat_InitFromStringImplementation))
			.Function("FindBetween", static_cast<void*>(FQuatImplementation::Quat_FindBetweenImplementation))
			.Function("FindBetweenNormals",
			          static_cast<void*>(FQuatImplementation::Quat_FindBetweenNormalsImplementation))
			.Function("FindBetweenVectors",
			          static_cast<void*>(FQuatImplementation::Quat_FindBetweenVectorsImplementation))
			.Function("Error", static_cast<void*>(FQuatImplementation::Quat_ErrorImplementation))
			.Function("ErrorAutoNormalize",
			          static_cast<void*>(FQuatImplementation::Quat_ErrorAutoNormalizeImplementation))
			.Function("FastLerp", static_cast<void*>(FQuatImplementation::Quat_FastLerpImplementation))
			.Function("FastBilerp", static_cast<void*>(FQuatImplementation::Quat_FastBilerpImplementation))
			.Function("Slerp_NotNormalized",
			          static_cast<void*>(FQuatImplementation::Quat_Slerp_NotNormalizedImplementation))
			.Function("Slerp", static_cast<void*>(FQuatImplementation::Quat_SlerpImplementation))
			.Function("SlerpFullPath_NotNormalized",
			          static_cast<void*>(FQuatImplementation::Quat_SlerpFullPath_NotNormalizedImplementation))
			.Function("SlerpFullPath", static_cast<void*>(FQuatImplementation::Quat_SlerpFullPathImplementation))
			.Function("Squad", static_cast<void*>(FQuatImplementation::Quat_SquadImplementation))
			.Function("SquadFull", static_cast<void*>(FQuatImplementation::Quat_SquadFullPathImplementation))
			.Function("CalcTangents", static_cast<void*>(FQuatImplementation::Quat_CalcTangentsImplementation))
			.Register();
	}
};

static FRegisterQuat RegisterQuat;

void FQuatImplementation::Quat_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
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

void FQuatImplementation::Quat_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
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

bool FQuatImplementation::Quat_EqualsImplementation(const MonoObject* A, const MonoObject* B, const float Tolerance)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->Equals(*QuatB, Tolerance);
	}

	return false;
}

bool FQuatImplementation::Quat_IsIdentityImplementation(const MonoObject* InMonoObject, const float Tolerance)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	if (Quat != nullptr)
	{
		return Quat->IsIdentity(Tolerance);
	}

	return false;
}

void FQuatImplementation::Quat_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
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

void FQuatImplementation::Quat_MultiplyVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                            MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

void FQuatImplementation::Quat_MultiplyMatrixImplementation(const MonoObject* InMonoObject, const MonoObject* M,
                                                            MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

void FQuatImplementation::Quat_MultiplyScaleImplementation(const MonoObject* InMonoObject, const float Scale,
                                                           MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->operator*(Scale);
	}
}

void FQuatImplementation::Quat_DivideImplementation(const MonoObject* InMonoObject, const float Scale,
                                                    MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->operator/(Scale);
	}
}

bool FQuatImplementation::Quat_IdenticalImplementation(const MonoObject* InMonoObject, const MonoObject* Q,
                                                       const uint32 PortFlags)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto QuatQ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	if (Quat != nullptr && QuatQ != nullptr)
	{
		return Quat->Identical(QuatQ, PortFlags);
	}

	return false;
}

bool FQuatImplementation::Quat_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->operator==(*QuatB);
	}

	return false;
}

bool FQuatImplementation::Quat_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto QuatA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(A);

	const auto QuatB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(B);

	if (QuatA != nullptr && QuatB != nullptr)
	{
		return QuatA->operator!=(*QuatB);
	}

	return false;
}

float FQuatImplementation::Quat_DotProductImplementation(const MonoObject* A, const MonoObject* B)
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

void FQuatImplementation::Quat_EulerImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->Euler();
	}
}

void FQuatImplementation::Quat_NormalizeImplementation(const MonoObject* InMonoObject, const float Tolerance)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject))
	{
		Quat->Normalize(Tolerance);
	}
}

void FQuatImplementation::Quat_GetNormalizedImplementation(const MonoObject* InMonoObject, const float Tolerance,
                                                           MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->GetNormalized(Tolerance);
	}
}

bool FQuatImplementation::Quat_IsNormalizedImplementation(const MonoObject* InMonoObject)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject))
	{
		return Quat->IsNormalized();
	}

	return false;
}

float FQuatImplementation::Quat_SizeImplementation(const MonoObject* InMonoObject)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject))
	{
		return Quat->Size();
	}

	return 0.f;
}

float FQuatImplementation::Quat_SizeSquaredImplementation(const MonoObject* InMonoObject)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject))
	{
		return Quat->SizeSquared();
	}

	return 0.f;
}

float FQuatImplementation::Quat_GetAngleImplementation(const MonoObject* InMonoObject)
{
	if (const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject))
	{
		return Quat->GetAngle();
	}

	return 0.f;
}

void FQuatImplementation::Quat_ToAxisAndAngleImplementation(const MonoObject* InMonoObject, MonoObject** Axis,
                                                            float& Angle)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		Quat->ToAxisAndAngle(*OutVector, Angle);
	}
}

void FQuatImplementation::Quat_ToSwingTwistImplementation(const MonoObject* InMonoObject, const MonoObject* InTwistAxis,
                                                          MonoObject** OutSwing, MonoObject** OutTwist)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

float FQuatImplementation::Quat_GetTwistAngleImplementation(const MonoObject* InMonoObject, const MonoObject* TwistAxis)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(TwistAxis);

	if (Quat != nullptr)
	{
		return Quat->GetTwistAngle(*Vector);
	}

	return 0.f;
}

void FQuatImplementation::Quat_RotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                          MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

void FQuatImplementation::Quat_UnrotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                            MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

void FQuatImplementation::Quat_LogImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Log();
	}
}

void FQuatImplementation::Quat_ExpImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Exp();
	}
}

void FQuatImplementation::Quat_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Quat != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Quat->Inverse();
	}
}

void FQuatImplementation::Quat_EnforceShortestArcWithImplementation(const MonoObject* InMonoObject,
                                                                    const MonoObject* OtherQuat)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto QuatOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(OtherQuat);

	if (Quat != nullptr && QuatOther != nullptr)
	{
		Quat->EnforceShortestArcWith(*QuatOther);
	}
}

void FQuatImplementation::Quat_GetAxisXImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisX();
	}
}

void FQuatImplementation::Quat_GetAxisYImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisY();
	}
}

void FQuatImplementation::Quat_GetAxisZImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetAxisZ();
	}
}

void FQuatImplementation::Quat_GetForwardVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetForwardVector();
	}
}

void FQuatImplementation::Quat_GetRightVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetRightVector();
	}
}

void FQuatImplementation::Quat_GetUpVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetUpVector();
	}
}

void FQuatImplementation::Quat_VectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->Vector();
	}
}

void FQuatImplementation::Quat_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Quat != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Quat->Rotator();
	}
}

void FQuatImplementation::Quat_GetRotationAxisImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Quat != nullptr && OutVector != nullptr)
	{
		*OutVector = Quat->GetRotationAxis();
	}
}

float FQuatImplementation::Quat_AngularDistanceImplementation(const MonoObject* InMonoObject, const MonoObject* Q)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	const auto QuatQ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q);

	if (Quat != nullptr && QuatQ != nullptr)
	{
		return Quat->AngularDistance(*QuatQ);
	}

	return 0.f;
}

bool FQuatImplementation::Quat_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

	if (Quat != nullptr)
	{
		return Quat->ContainsNaN();
	}

	return false;
}

void FQuatImplementation::Quat_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

bool FQuatImplementation::Quat_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString)
{
	const auto Quat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(InMonoObject);

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

float FQuatImplementation::Quat_ErrorImplementation(const MonoObject* Q1, const MonoObject* Q2)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q2);

	if (Quat1 != nullptr && Quat2 != nullptr)
	{
		return FQuat::Error(*Quat1, *Quat2);
	}

	return 0.f;
}

float FQuatImplementation::Quat_ErrorAutoNormalizeImplementation(const MonoObject* Q1, const MonoObject* Q2)
{
	const auto Quat1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q1);

	const auto Quat2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(Q2);

	if (Quat1 != nullptr && Quat2 != nullptr)
	{
		return FQuat::ErrorAutoNormalize(*Quat1, *Quat2);
	}

	return 0.f;
}

void FQuatImplementation::Quat_FastLerpImplementation(const MonoObject* A, const MonoObject* B, const float Alpha,
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

void FQuatImplementation::Quat_FastBilerpImplementation(const MonoObject* P00, const MonoObject* P10,
                                                        const MonoObject* P01, const MonoObject* P11, const float FracX,
                                                        const float FracY, MonoObject** OutValue)
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

void FQuatImplementation::Quat_Slerp_NotNormalizedImplementation(const MonoObject* Quat1, const MonoObject* Quat2,
                                                                 const float Slerp, MonoObject** OutValue)
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

void FQuatImplementation::Quat_SlerpImplementation(const MonoObject* Quat1, const MonoObject* Quat2, const float Slerp,
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
	const MonoObject* quat1, const MonoObject* quat2, const float Alpha, MonoObject** OutValue)
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

void FQuatImplementation::Quat_SlerpFullPathImplementation(const MonoObject* quat1, const MonoObject* quat2,
                                                           const float Alpha, MonoObject** OutValue)
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

void FQuatImplementation::Quat_SquadImplementation(const MonoObject* quat1, const MonoObject* tang1,
                                                   const MonoObject* quat2, const MonoObject* tang2, const float Alpha,
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

void FQuatImplementation::Quat_SquadFullPathImplementation(const MonoObject* quat1, const MonoObject* tang1,
                                                           const MonoObject* quat2, const MonoObject* tang2,
                                                           const float Alpha, MonoObject** OutValue)
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

void FQuatImplementation::Quat_CalcTangentsImplementation(const MonoObject* PrevP, const MonoObject* P,
                                                          const MonoObject* NextP, const float Tension,
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
