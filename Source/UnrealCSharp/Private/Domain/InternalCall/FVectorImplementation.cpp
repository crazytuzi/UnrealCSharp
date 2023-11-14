#include "Domain/InternalCall/FVectorImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector
{
	FRegisterVector()
	{
		TReflectionClassBuilder<FVector>(NAMESPACE_LIBRARY)
			.Function("CrossProduct", FVectorImplementation::Vector_CrossProductImplementation)
			.Function("DotProduct", FVectorImplementation::Vector_DotProductImplementation)
			.Function("Add", FVectorImplementation::Vector_AddImplementation)
			.Function("AddBias", FVectorImplementation::Vector_AddBiasImplementation)
			.Function("Subtract", FVectorImplementation::Vector_SubtractImplementation)
			.Function("SubtractBias", FVectorImplementation::Vector_SubtractBiasImplementation)
			.Function("Multiply", FVectorImplementation::Vector_MultiplyImplementation)
			.Function("MultiplyScale", FVectorImplementation::Vector_MultiplyScaleImplementation)
			.Function("Divide", FVectorImplementation::Vector_DivideImplementation)
			.Function("DivideScale", FVectorImplementation::Vector_DivideScaleImplementation)
			.Function("Equals", FVectorImplementation::Vector_EqualsImplementation)
			.Function("AllComponentsEqual", FVectorImplementation::Vector_AllComponentsEqualImplementation)
			.Function("Negated", FVectorImplementation::Vector_NegatedImplementation)
			.Function("GetComponent", FVectorImplementation::Vector_GetComponentImplementation)
			.Function("SetComponent", FVectorImplementation::Vector_SetComponentImplementation)
			.Function("Component", FVectorImplementation::Vector_ComponentImplementation)
			.Function("Set", FVectorImplementation::Vector_SetImplementation)
			.Function("GetMax", FVectorImplementation::Vector_GetMaxImplementation)
			.Function("GetAbsMax", FVectorImplementation::Vector_GetAbsMaxImplementation)
			.Function("GetMin", FVectorImplementation::Vector_GetMinImplementation)
			.Function("GetAbsMin", FVectorImplementation::Vector_GetAbsMinImplementation)
			.Function("ComponentMin", FVectorImplementation::Vector_ComponentMinImplementation)
			.Function("ComponentMax", FVectorImplementation::Vector_ComponentMaxImplementation)
			.Function("GetAbs", FVectorImplementation::Vector_GetAbsImplementation)
			.Function("Size", FVectorImplementation::Vector_SizeImplementation)
			.Function("SizeSquared", FVectorImplementation::Vector_SizeSquaredImplementation)
			.Function("Size2D", FVectorImplementation::Vector_Size2DImplementation)
			.Function("SizeSquared2D", FVectorImplementation::Vector_SizeSquared2DImplementation)
			.Function("IsNearlyZero", FVectorImplementation::Vector_IsNearlyZeroImplementation)
			.Function("IsZero", FVectorImplementation::Vector_IsZeroImplementation)
			.Function("IsUnit", FVectorImplementation::Vector_IsUnitImplementation)
			.Function("IsNormalized", FVectorImplementation::Vector_IsNormalizedImplementation)
			.Function("Normalize", FVectorImplementation::Vector_NormalizeImplementation)
			.Function("GetUnsafeNormal", FVectorImplementation::Vector_GetUnsafeNormalImplementation)
			.Function("GetSafeNormal", FVectorImplementation::Vector_GetSafeNormalImplementation)
			.Function("GetSafeNormal2D", FVectorImplementation::Vector_GetSafeNormal2DImplementation)
			.Function("ToDirectionAndLength", FVectorImplementation::Vector_ToDirectionAndLengthImplementation)
			.Function("GetSignVector", FVectorImplementation::Vector_GetSignVectorImplementation)
			.Function("Projection", FVectorImplementation::Vector_ProjectionImplementation)
			.Function("GetUnsafeNormal2D", FVectorImplementation::Vector_GetUnsafeNormal2DImplementation)
			.Function("GridSnap", FVectorImplementation::Vector_GridSnapImplementation)
			.Function("BoundToCube", FVectorImplementation::Vector_BoundToCubeImplementation)
			.Function("BoundToBox", FVectorImplementation::Vector_BoundToBoxImplementation)
			.Function("GetClampedToSize", FVectorImplementation::Vector_GetClampedToSizeImplementation)
			.Function("GetClampedToSize2D", FVectorImplementation::Vector_GetClampedToSize2DImplementation)
			.Function("GetClampedToMaxSize", FVectorImplementation::Vector_GetClampedToMaxSizeImplementation)
			.Function("GetClampedToMaxSize2D", FVectorImplementation::Vector_GetClampedToMaxSize2DImplementation)
			.Function("AddBounded", FVectorImplementation::Vector_AddBoundedImplementation)
			.Function("Reciprocal", FVectorImplementation::Vector_ReciprocalImplementation)
			.Function("IsUniform", FVectorImplementation::Vector_IsUniformImplementation)
			.Function("MirrorByVector", FVectorImplementation::Vector_MirrorByVectorImplementation)
			.Function("MirrorByPlane", FVectorImplementation::Vector_MirrorByPlaneImplementation)
			.Function("RotateAngleAxis", FVectorImplementation::Vector_RotateAngleAxisImplementation)
			.Function("CosineAngle2D", FVectorImplementation::Vector_CosineAngle2DImplementation)
			.Function("ProjectOnTo", FVectorImplementation::Vector_ProjectOnToImplementation)
			.Function("ProjectOnToNormal", FVectorImplementation::Vector_ProjectOnToNormalImplementation)
			.Function("ToOrientationRotator", FVectorImplementation::Vector_ToOrientationRotatorImplementation)
			.Function("ToOrientationQuat", FVectorImplementation::Vector_ToOrientationQuatImplementation)
			.Function("Rotation", FVectorImplementation::Vector_RotationImplementation)
			.Function("FindBestAxisVectors", FVectorImplementation::Vector_FindBestAxisVectorsImplementation)
			.Function("UnwindEuler", FVectorImplementation::Vector_UnwindEulerImplementation)
			.Function("ContainsNaN", FVectorImplementation::Vector_ContainsNaNImplementation)
			.Function("ToString", FVectorImplementation::Vector_ToStringImplementation)
			.Function("ToText", FVectorImplementation::Vector_ToTextImplementation)
			.Function("ToCompactString", FVectorImplementation::Vector_ToCompactStringImplementation)
			.Function("ToCompactText", FVectorImplementation::Vector_ToCompactTextImplementation)
			.Function("InitFromString", FVectorImplementation::Vector_InitFromStringImplementation)
			.Function("UnitCartesianToSpherical", FVectorImplementation::Vector_UnitCartesianToSphericalImplementation)
			.Function("HeadingAngle", FVectorImplementation::Vector_HeadingAngleImplementation)
			.Function("CreateOrthonormalBasis", FVectorImplementation::Vector_CreateOrthonormalBasisImplementation)
			.Function("PointsAreSame", FVectorImplementation::Vector_PointsAreSameImplementation)
			.Function("PointsAreNear", FVectorImplementation::Vector_PointsAreNearImplementation)
			.Function("PointPlaneDist", FVectorImplementation::Vector_PointPlaneDistImplementation)
			.Function("PointPlaneProjectByPlane", FVectorImplementation::Vector_PointPlaneProjectByPlaneImplementation)
			.Function("PointPlaneProjectByPoints",
			          FVectorImplementation::Vector_PointPlaneProjectByPointsImplementation)
			.Function("PointPlaneProjectByPlaneBaseAndPlaneNormal",
			          FVectorImplementation::Vector_PointPlaneProjectByPlaneBaseAndPlaneNormalImplementation)
			.Function("VectorPlaneProject", FVectorImplementation::Vector_VectorPlaneProjectImplementation)
			.Function("Dist", FVectorImplementation::Vector_DistImplementation)
			.Function("Distance", FVectorImplementation::Vector_DistanceImplementation)
			.Function("DistXY", FVectorImplementation::Vector_DistXYImplementation)
			.Function("Dist2D", FVectorImplementation::Vector_Dist2DImplementation)
			.Function("DistSquared", FVectorImplementation::Vector_DistSquaredImplementation)
			.Function("DistSquaredXY", FVectorImplementation::Vector_DistSquaredXYImplementation)
			.Function("DistSquared2D", FVectorImplementation::Vector_DistSquared2DImplementation)
			.Function("BoxPushOut", FVectorImplementation::Vector_BoxPushOutImplementation)
			.Function("Parallel", FVectorImplementation::Vector_ParallelImplementation)
			.Function("Coincident", FVectorImplementation::Vector_CoincidentImplementation)
			.Function("Orthogonal", FVectorImplementation::Vector_OrthogonalImplementation)
			.Function("Coplanar", FVectorImplementation::Vector_CoplanarImplementation)
			.Function("Triple", FVectorImplementation::Vector_TripleImplementation)
			.Function("RadiansToDegrees", FVectorImplementation::Vector_RadiansToDegreesImplementation)
			.Function("DegreesToRadians", FVectorImplementation::Vector_DegreesToRadiansImplementation)
			.Register();
	}
};

static FRegisterVector RegisterVector;

void FVectorImplementation::Vector_CrossProductImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->operator^(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DotProductImplementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	if (VectorA != nullptr && VectorB != nullptr)
	{
		return VectorA->operator|(*VectorB);
	}

	return 0.f;
}

void FVectorImplementation::Vector_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                     MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->operator+(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_AddBiasImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const LwcType Bias, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->operator+(Bias));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_SubtractImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->operator-(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_SubtractBiasImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const LwcType Bias, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->operator-(Bias));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->operator*(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const LwcType Scale, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->operator*(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_DivideImplementation(const FGarbageCollectionHandle A,
                                                        const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->operator/(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_DivideScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             const LwcType Scale, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->operator/(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

bool FVectorImplementation::Vector_EqualsImplementation(const FGarbageCollectionHandle A,
                                                        const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	if (VectorA != nullptr && VectorB != nullptr)
	{
		return VectorA->Equals(*VectorB, Tolerance);
	}

	return false;
}

bool FVectorImplementation::Vector_AllComponentsEqualImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->AllComponentsEqual(Tolerance);
	}

	return false;
}

void FVectorImplementation::Vector_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->operator-());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_GetComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 InIndex)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->operator[](InIndex);
	}

	return 0.f;
}

void FVectorImplementation::Vector_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const int32 InIndex, const LwcType InValue)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		Vector->operator[](InIndex) = InValue;
	}
}

FVectorImplementation::LwcType FVectorImplementation::Vector_ComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 InIndex)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->Component(InIndex);
	}

	return 0.f;
}

void FVectorImplementation::Vector_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     const LwcType InX, const LwcType InY, const LwcType InZ)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		Vector->Set(InX, InY, InZ);
	}
}

FVectorImplementation::LwcType FVectorImplementation::Vector_GetMaxImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->GetMax();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_GetAbsMaxImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->GetAbsMax();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_GetMinImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->GetMin();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_GetAbsMinImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->GetAbsMin();
	}

	return 0.f;
}

void FVectorImplementation::Vector_ComponentMinImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->ComponentMin(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ComponentMaxImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(VectorA->ComponentMax(*VectorB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetAbsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetAbs());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_SizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->Size();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_SizeSquaredImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->SizeSquared();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_Size2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->Size2D();
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_SizeSquared2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->SizeSquared2D();
	}

	return 0.f;
}

bool FVectorImplementation::Vector_IsNearlyZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const LwcType Tolerance)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->IsNearlyZero(Tolerance);
	}

	return false;
}

bool FVectorImplementation::Vector_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->IsZero();
	}

	return false;
}

bool FVectorImplementation::Vector_IsUnitImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const LwcType LengthSquaredTolerance)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->IsUnit(LengthSquaredTolerance);
	}

	return false;
}

bool FVectorImplementation::Vector_IsNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->IsNormalized();
	}

	return false;
}

bool FVectorImplementation::Vector_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const LwcType Tolerance)
{
	if (const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle))
	{
		return Vector->Normalize(Tolerance);
	}

	return false;
}

void FVectorImplementation::Vector_GetUnsafeNormalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetUnsafeNormal());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetSafeNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetSafeNormal(Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetSafeNormal2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetSafeNormal2D(Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ToDirectionAndLengthImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutDir, LwcType& OutLength)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutDir = NewMonoObject;

	const auto OutVector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);

	Vector->ToDirectionAndLength(*OutVector, OutLength);
}

void FVectorImplementation::Vector_GetSignVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetSignVector());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ProjectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->Projection());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetUnsafeNormal2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetUnsafeNormal2D());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GridSnapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const LwcType GridSz, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GridSnap(GridSz));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_BoundToCubeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             const LwcType Radius, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->BoundToCube(Radius));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_BoundToBoxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* Min, const MonoObject* Max,
                                                            MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorMin = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Min);

	const auto VectorMax = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Max);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->BoundToBox(*VectorMin, *VectorMax));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetClampedToSizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Min, const LwcType Max,
	MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetClampedToSize(Min, Max));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetClampedToSize2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Min, const LwcType Max,
	MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetClampedToSize2D(Min, Max));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetClampedToMaxSizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType MaxSize, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetClampedToMaxSize(MaxSize));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_GetClampedToMaxSize2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType MaxSize, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->GetClampedToMaxSize2D(MaxSize));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_AddBoundedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* V, const LwcType Radius)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorV = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	if (Vector != nullptr && VectorV != nullptr)
	{
		Vector->AddBounded(*VectorV, Radius);
	}
}

void FVectorImplementation::Vector_ReciprocalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->Reciprocal());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

bool FVectorImplementation::Vector_IsUniformImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const LwcType Tolerance)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		return Vector->IsUniform(Tolerance);
	}

	return false;
}

void FVectorImplementation::Vector_MirrorByVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* MirrorNormal, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorMirrorNormal = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector>(MirrorNormal);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->MirrorByVector(*VectorMirrorNormal));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_MirrorByPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const MonoObject* Plane, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto PlanePlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(Plane);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->MirrorByPlane(*PlanePlane));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_RotateAngleAxisImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType AngleDeg,
	const FGarbageCollectionHandle Axis, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorAxis = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->RotateAngleAxis(AngleDeg, *VectorAxis));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_CosineAngle2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const FGarbageCollectionHandle B)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	if (Vector != nullptr && VectorB != nullptr)
	{
		return Vector->CosineAngle2D(*VectorB);
	}

	return 0.f;
}

void FVectorImplementation::Vector_ProjectOnToImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             const FGarbageCollectionHandle A, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->ProjectOnTo(*VectorA));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ProjectOnToNormalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Normal, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto VectorNormal = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Vector->ProjectOnToNormal(*VectorNormal));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ToOrientationRotatorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = new FRotator(Vector->ToOrientationRotator());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FRotator>::Get(), OutRotator,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_ToOrientationQuatImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = new FQuat(Vector->ToOrientationQuat());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FQuat>::Get(), OutQuat,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_RotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = new FRotator(Vector->Rotation());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FRotator>::Get(), OutRotator,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_FindBestAxisVectorsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** Axis1, MonoObject** Axis2)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis1 = NewMonoObject1;

	const auto OutAxis1Vector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutAxis1Vector,
	                                                        NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis2 = NewMonoObject2;

	const auto OutAxis2Vector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutAxis2Vector,
	                                                        NewMonoObject2);

	if (Vector != nullptr && OutAxis1Vector != nullptr && OutAxis2Vector != nullptr)
	{
		Vector->FindBestAxisVectors(*OutAxis1Vector, *OutAxis2Vector);
	}
}

void FVectorImplementation::Vector_UnwindEulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		Vector->UnwindEuler();
	}
}

bool FVectorImplementation::Vector_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		return Vector->ContainsNaN();
	}

	return false;
}

void FVectorImplementation::Vector_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		const auto ResultString = Vector->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FVectorImplementation::Vector_ToTextImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		const auto ResultText = Vector->ToText();

		const auto FoundMonoClass = TPropertyClass<FText, FText>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultText.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FVectorImplementation::Vector_ToCompactStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		const auto ResultString = Vector->ToCompactString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FVectorImplementation::Vector_ToCompactTextImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		const auto ResultText = Vector->ToCompactText();

		const auto FoundMonoClass = TPropertyClass<FText, FText>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultText.ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FVectorImplementation::Vector_InitFromStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InSourceString)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr && InSourceString != nullptr)
	{
		return Vector->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FVectorImplementation::Vector_UnitCartesianToSphericalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Vector->UnitCartesianToSpherical());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_HeadingAngleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(
		InGarbageCollectionHandle);

	if (Vector != nullptr)
	{
		return Vector->HeadingAngle();
	}

	return false;
}

void FVectorImplementation::Vector_CreateOrthonormalBasisImplementation(MonoObject** XAxis, MonoObject** YAxis,
                                                                        MonoObject** ZAxis)
{
	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*XAxis = NewMonoObject1;

	const auto OutXAxisVector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutXAxisVector,
	                                                        NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*YAxis = NewMonoObject2;

	const auto OutYAxisVector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutYAxisVector,
	                                                        NewMonoObject2);

	const auto NewMonoObject3 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*ZAxis = NewMonoObject3;

	const auto OutZAxisVector = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutZAxisVector,
	                                                        NewMonoObject3);

	FVector::CreateOrthonormalBasis(*OutXAxisVector, *OutYAxisVector, *OutZAxisVector);
}

bool FVectorImplementation::Vector_PointsAreSameImplementation(const MonoObject* P, const MonoObject* Q)
{
	const auto VectorP = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(P);

	const auto VectorQ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Q);

	if (VectorP != nullptr && VectorQ != nullptr)
	{
		return FVector::PointsAreSame(*VectorP, *VectorQ);
	}

	return false;
}

bool FVectorImplementation::Vector_PointsAreNearImplementation(const MonoObject* Point1, const MonoObject* Point2,
                                                               const LwcType Dist)
{
	const auto VectorPoint1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point1);

	const auto VectorPoint2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point2);

	if (VectorPoint1 != nullptr && VectorPoint2 != nullptr)
	{
		return FVector::PointsAreNear(*VectorPoint1, *VectorPoint2, Dist);
	}

	return false;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_PointPlaneDistImplementation(
	const MonoObject* Point, const MonoObject* PlaneBase, const MonoObject* PlaneNormal)
{
	const auto VectorPoint = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point);

	const auto VectorPlaneBase = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(PlaneBase);

	const auto VectorPlaneNormal = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector>(PlaneNormal);

	if (VectorPoint != nullptr && VectorPlaneBase != nullptr && VectorPlaneNormal != nullptr)
	{
		return FVector::PointPlaneDist(*VectorPoint, *VectorPlaneBase, *VectorPlaneNormal);
	}

	return false;
}

void FVectorImplementation::Vector_PointPlaneProjectByPlaneImplementation(
	const MonoObject* Point, const MonoObject* Plane, MonoObject** OutValue)
{
	const auto VectorPoint = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point);

	const auto PlanePlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(Plane);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::PointPlaneProject(*VectorPoint, *PlanePlane));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_PointPlaneProjectByPointsImplementation(
	const MonoObject* Point, const FGarbageCollectionHandle A, const FGarbageCollectionHandle B, const MonoObject* C,
	MonoObject** OutValue)
{
	const auto VectorPoint = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point);

	const auto VectorA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(A);

	const auto VectorB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(B);

	const auto VectorC = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(C);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::PointPlaneProject(*VectorPoint, *VectorA, *VectorB, *VectorC));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_PointPlaneProjectByPlaneBaseAndPlaneNormalImplementation(
	const MonoObject* Point, const MonoObject* PlaneBase, const MonoObject* PlaneNormal, MonoObject** OutValue)
{
	const auto VectorPoint = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Point);

	const auto VectorPlaneBase = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(PlaneBase);

	const auto VectorPlaneNormal = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector>(PlaneNormal);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::PointPlaneProject(*VectorPoint, *VectorPlaneBase, *VectorPlaneNormal));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_VectorPlaneProjectImplementation(const MonoObject* V, const MonoObject* PlaneNormal,
                                                                    MonoObject** OutValue)
{
	const auto VectorV = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto VectorPlaneNormal = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector>(PlaneNormal);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::VectorPlaneProject(*VectorV, *VectorPlaneNormal));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::Dist(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistanceImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::Distance(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistXYImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::DistXY(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_Dist2DImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::Dist2D(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistSquaredImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::DistSquared(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistSquaredXYImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::DistSquaredXY(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_DistSquared2DImplementation(
	const MonoObject* V1, const MonoObject* V2)
{
	const auto VectorV1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V1);

	const auto VectorV2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V2);

	if (VectorV1 != nullptr && VectorV2 != nullptr)
	{
		return FVector::DistSquared2D(*VectorV1, *VectorV2);
	}

	return 0.f;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_BoxPushOutImplementation(
	const MonoObject* Normal, const MonoObject* Size)
{
	const auto VectorNormal = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal);

	const auto VectorSize = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Size);

	if (VectorNormal != nullptr && VectorSize != nullptr)
	{
		return FVector::BoxPushOut(*VectorNormal, *VectorSize);
	}

	return 0.f;
}

bool FVectorImplementation::Vector_ParallelImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
                                                          const LwcType ParallelCosineThreshold)
{
	const auto VectorNormal1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal1);

	const auto VectorNormal2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal2);

	if (VectorNormal1 != nullptr && VectorNormal2 != nullptr)
	{
		return FVector::Parallel(*VectorNormal1, *VectorNormal2, ParallelCosineThreshold);
	}

	return false;
}

bool FVectorImplementation::Vector_CoincidentImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
                                                            const LwcType ParallelCosineThreshold)
{
	const auto VectorNormal1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal1);

	const auto VectorNormal2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal2);

	if (VectorNormal1 != nullptr && VectorNormal2 != nullptr)
	{
		return FVector::Coincident(*VectorNormal1, *VectorNormal2, ParallelCosineThreshold);
	}

	return false;
}

bool FVectorImplementation::Vector_OrthogonalImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
                                                            const LwcType ParallelCosineThreshold)
{
	const auto VectorNormal1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal1);

	const auto VectorNormal2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal2);

	if (VectorNormal1 != nullptr && VectorNormal2 != nullptr)
	{
		return FVector::Orthogonal(*VectorNormal1, *VectorNormal2, ParallelCosineThreshold);
	}

	return false;
}

bool FVectorImplementation::Vector_CoplanarImplementation(const FGarbageCollectionHandle Base1,
                                                          const MonoObject* Normal1,
                                                          const FGarbageCollectionHandle Base2,
                                                          const MonoObject* Normal2,
                                                          const LwcType ParallelCosineThreshold)
{
	const auto VectorBase1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Base1);

	const auto VectorNormal1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal1);

	const auto VectorBase2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Base2);

	const auto VectorNormal2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Normal2);

	if (VectorBase1 != nullptr && VectorNormal1 != nullptr && VectorBase2 != nullptr && VectorNormal2 != nullptr)
	{
		return FVector::Coplanar(*VectorBase1, *VectorNormal1, *VectorNormal2, *VectorNormal2, ParallelCosineThreshold);
	}

	return false;
}

FVectorImplementation::LwcType FVectorImplementation::Vector_TripleImplementation(
	const MonoObject* X, const MonoObject* Y, const MonoObject* Z)
{
	const auto VectorX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(X);

	const auto VectorY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Y);

	const auto VectorZ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Z);

	if (VectorX != nullptr && VectorY != nullptr && VectorZ != nullptr)
	{
		return FVector::Triple(*VectorX, *VectorY, *VectorZ);
	}

	return 0.f;
}

void FVectorImplementation::Vector_RadiansToDegreesImplementation(const MonoObject* RadVector, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(RadVector);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::RadiansToDegrees(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FVectorImplementation::Vector_DegreesToRadiansImplementation(const MonoObject* DegVector, MonoObject** OutValue)
{
	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(DegVector);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(FVector::DegreesToRadians(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}
