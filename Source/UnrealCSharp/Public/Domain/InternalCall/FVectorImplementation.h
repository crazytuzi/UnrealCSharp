#pragma once

#include "UEVersion.h"
#include "mono/metadata/object-forward.h"

class FVectorImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Vector_CrossProductImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static LwcType Vector_DotProductImplementation(const MonoObject* A, const MonoObject* B);

	static void Vector_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector_AddBiasImplementation(const MonoObject* InMonoObject, LwcType Bias, MonoObject** OutValue);

	static void Vector_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector_SubtractBiasImplementation(const MonoObject* InMonoObject, LwcType Bias, MonoObject** OutValue);

	static void Vector_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector_MultiplyScaleImplementation(const MonoObject* InMonoObject, LwcType Scale,
	                                               MonoObject** OutValue);

	static void Vector_DivideImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector_DivideScaleImplementation(const MonoObject* InMonoObject, LwcType Scale, MonoObject** OutValue);

	static bool Vector_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector_EqualsImplementation(const MonoObject* A, const MonoObject* B, LwcType Tolerance);

	static bool Vector_AllComponentsEqualImplementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static void Vector_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static LwcType Vector_GetComponentImplementation(const MonoObject* InMonoObject, int32 InIndex);

	static void Vector_SetComponentImplementation(const MonoObject* InMonoObject, int32 InIndex, LwcType InValue);

	static LwcType Vector_ComponentImplementation(const MonoObject* InMonoObject, int32 InIndex);

	static void Vector_SetImplementation(const MonoObject* InMonoObject, LwcType InX, LwcType InY, LwcType InZ);

	static LwcType Vector_GetMaxImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_GetAbsMaxImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_GetMinImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_GetAbsMinImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_SizeImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_SizeSquaredImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_Size2DImplementation(const MonoObject* InMonoObject);

	static LwcType Vector_SizeSquared2DImplementation(const MonoObject* InMonoObject);

	static bool Vector_IsNearlyZeroImplementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static bool Vector_IsZeroImplementation(const MonoObject* InMonoObject);

	static bool Vector_IsUnitImplementation(const MonoObject* InMonoObject, LwcType LengthSquaredTolerance);

	static bool Vector_IsNormalizedImplementation(const MonoObject* InMonoObject);

	static bool Vector_NormalizeImplementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static void Vector_GetUnsafeNormalImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_GetSafeNormalImplementation(const MonoObject* InMonoObject, LwcType Tolerance,
	                                               MonoObject** OutValue);

	static void Vector_GetSafeNormal2DImplementation(const MonoObject* InMonoObject, LwcType Tolerance,
	                                                 MonoObject** OutValue);

	static void Vector_ToDirectionAndLengthImplementation(const MonoObject* InMonoObject, MonoObject** OutDir,
	                                                      LwcType& OutLength);

	static void Vector_GetSignVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_ProjectionImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_GetUnsafeNormal2DImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_GridSnapImplementation(const MonoObject* InMonoObject, LwcType GridSz, MonoObject** OutValue);

	static void Vector_BoundToCubeImplementation(const MonoObject* InMonoObject, LwcType Radius, MonoObject** OutValue);

	static void Vector_BoundToBoxImplementation(const MonoObject* InMonoObject, const MonoObject* Min,
	                                            const MonoObject* Max, MonoObject** OutValue);

	static void Vector_GetClampedToSizeImplementation(const MonoObject* InMonoObject, LwcType Min, LwcType Max,
	                                                  MonoObject** OutValue);

	static void Vector_GetClampedToSize2DImplementation(const MonoObject* InMonoObject, LwcType Min, LwcType Max,
	                                                    MonoObject** OutValue);

	static void Vector_GetClampedToMaxSizeImplementation(const MonoObject* InMonoObject, LwcType MaxSize,
	                                                     MonoObject** OutValue);

	static void Vector_GetClampedToMaxSize2DImplementation(const MonoObject* InMonoObject, LwcType MaxSize,
	                                                       MonoObject** OutValue);

	static void Vector_AddBoundedImplementation(const MonoObject* InMonoObject, const MonoObject* V, LwcType Radius);

	static void Vector_ReciprocalImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Vector_IsUniformImplementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static void Vector_MirrorByVectorImplementation(const MonoObject* InMonoObject, const MonoObject* MirrorNormal,
	                                                MonoObject** OutValue);

	static void Vector_MirrorByPlaneImplementation(const MonoObject* InMonoObject, const MonoObject* Plane,
	                                               MonoObject** OutValue);

	static void Vector_RotateAngleAxisImplementation(const MonoObject* InMonoObject, LwcType AngleDeg,
	                                                 const MonoObject* Axis, MonoObject** OutValue);

	static LwcType Vector_CosineAngle2DImplementation(const MonoObject* InMonoObject, const MonoObject* B);

	static void Vector_ProjectOnToImplementation(const MonoObject* InMonoObject, const MonoObject* A,
	                                             MonoObject** OutValue);

	static void Vector_ProjectOnToNormalImplementation(const MonoObject* InMonoObject, const MonoObject* Normal,
	                                                   MonoObject** OutValue);

	static void Vector_ToOrientationRotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_ToOrientationQuatImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_RotationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_FindBestAxisVectorsImplementation(const MonoObject* InMonoObject, MonoObject** Axis1,
	                                                     MonoObject** Axis2);

	static void Vector_UnwindEulerImplementation(const MonoObject* InMonoObject);

	static bool Vector_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static void Vector_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_ToTextImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_ToCompactStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector_ToCompactTextImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Vector_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static void Vector_UnitCartesianToSphericalImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static LwcType Vector_HeadingAngleImplementation(const MonoObject* InMonoObject);

	static void Vector_CreateOrthonormalBasisImplementation(MonoObject** XAxis, MonoObject** YAxis, MonoObject** ZAxis);

	static bool Vector_PointsAreSameImplementation(const MonoObject* P, const MonoObject* Q);

	static bool Vector_PointsAreNearImplementation(const MonoObject* Point1, const MonoObject* Point2, LwcType Dist);

	static LwcType Vector_PointPlaneDistImplementation(const MonoObject* Point, const MonoObject* PlaneBase,
	                                                   const MonoObject* PlaneNormal);

	static void Vector_PointPlaneProjectByPlaneImplementation(const MonoObject* Point, const MonoObject* Plane,
	                                                          MonoObject** OutValue);

	static void Vector_PointPlaneProjectByPointsImplementation(const MonoObject* Point, const MonoObject* A,
	                                                           const MonoObject* B, const MonoObject* C,
	                                                           MonoObject** OutValue);

	static void Vector_PointPlaneProjectByPlaneBaseAndPlaneNormalImplementation(
		const MonoObject* Point, const MonoObject* PlaneBase, const MonoObject* PlaneNormal, MonoObject** OutValue);

	static void Vector_VectorPlaneProjectImplementation(const MonoObject* V, const MonoObject* PlaneNormal,
	                                                    MonoObject** OutValue);

	static LwcType Vector_DistImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_DistanceImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_DistXYImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_Dist2DImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_DistSquaredImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_DistSquaredXYImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_DistSquared2DImplementation(const MonoObject* V1, const MonoObject* V2);

	static LwcType Vector_BoxPushOutImplementation(const MonoObject* Normal, const MonoObject* Size);

	static bool Vector_ParallelImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
	                                          LwcType ParallelCosineThreshold);

	static bool Vector_CoincidentImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
	                                            LwcType ParallelCosineThreshold);

	static bool Vector_OrthogonalImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
	                                            LwcType ParallelCosineThreshold);

	static bool Vector_CoplanarImplementation(const MonoObject* Base1, const MonoObject* Normal1,
	                                          const MonoObject* Base2, const MonoObject* Normal2,
	                                          LwcType ParallelCosineThreshold);

	static LwcType Vector_TripleImplementation(const MonoObject* X, const MonoObject* Y, const MonoObject* Z);

	static void Vector_RadiansToDegreesImplementation(const MonoObject* RadVector, MonoObject** OutValue);

	static void Vector_DegreesToRadiansImplementation(const MonoObject* DegVector, MonoObject** OutValue);
};
