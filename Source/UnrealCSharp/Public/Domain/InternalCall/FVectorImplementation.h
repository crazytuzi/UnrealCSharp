#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FVectorImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Vector_CrossProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static LwcType Vector_DotProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Vector_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                     MonoObject** OutValue);

	static void Vector_AddBiasImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Bias,
	                                         MonoObject** OutValue);

	static void Vector_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static void Vector_SubtractBiasImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              LwcType Bias, MonoObject** OutValue);

	static void Vector_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static void Vector_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Scale, MonoObject** OutValue);

	static void Vector_DivideImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        MonoObject** OutValue);

	static void Vector_DivideScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType Scale, MonoObject** OutValue);

	static bool Vector_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        LwcType Tolerance);

	static bool Vector_AllComponentsEqualImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    LwcType Tolerance);

	static void Vector_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static LwcType Vector_GetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 int32 InIndex);

	static void Vector_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              int32 InIndex, LwcType InValue);

	static LwcType Vector_ComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              int32 InIndex);

	static void Vector_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType InX,
	                                     LwcType InY, LwcType InZ);

	static LwcType Vector_GetMaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_GetAbsMaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_GetMinImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_GetAbsMinImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Vector_ComponentMinImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static void Vector_ComponentMaxImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static void Vector_GetAbsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static LwcType Vector_SizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_SizeSquaredImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_Size2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector_SizeSquared2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector_IsNearlyZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              LwcType Tolerance);

	static bool Vector_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector_IsUnitImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        LwcType LengthSquaredTolerance);

	static bool Vector_IsNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           LwcType Tolerance);

	static void Vector_GetUnsafeNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void Vector_GetSafeNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Tolerance, MonoObject** OutValue);

	static void Vector_GetSafeNormal2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 LwcType Tolerance, MonoObject** OutValue);

	static void Vector_ToDirectionAndLengthImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutDir, LwcType& OutLength);

	static void Vector_GetSignVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static void Vector_ProjectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void Vector_GetUnsafeNormal2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static void Vector_GridSnapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType GridSz,
	                                          MonoObject** OutValue);

	static void Vector_BoundToCubeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType Radius, MonoObject** OutValue);

	static void Vector_BoundToBoxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* Min, const MonoObject* Max, MonoObject** OutValue);

	static void Vector_GetClampedToSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  LwcType Min, LwcType Max, MonoObject** OutValue);

	static void Vector_GetClampedToSize2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    LwcType Min, LwcType Max, MonoObject** OutValue);

	static void Vector_GetClampedToMaxSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     LwcType MaxSize, MonoObject** OutValue);

	static void Vector_GetClampedToMaxSize2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       LwcType MaxSize, MonoObject** OutValue);

	static void Vector_AddBoundedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* V, LwcType Radius);

	static void Vector_ReciprocalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static bool Vector_IsUniformImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           LwcType Tolerance);

	static void Vector_MirrorByVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const MonoObject* MirrorNormal, MonoObject** OutValue);

	static void Vector_MirrorByPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const MonoObject* Plane, MonoObject** OutValue);

	static void Vector_RotateAngleAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 LwcType AngleDeg, const FGarbageCollectionHandle Axis,
	                                                 MonoObject** OutValue);

	static LwcType Vector_CosineAngle2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const FGarbageCollectionHandle B);

	static void Vector_ProjectOnToImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             const FGarbageCollectionHandle A, MonoObject** OutValue);

	static void Vector_ProjectOnToNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* Normal, MonoObject** OutValue);

	static void Vector_ToOrientationRotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutValue);

	static void Vector_ToOrientationQuatImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static void Vector_RotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Vector_FindBestAxisVectorsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** Axis1, MonoObject** Axis2);

	static void Vector_UnwindEulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Vector_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Vector_ToTextImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Vector_ToCompactStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void Vector_ToCompactTextImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static bool Vector_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject* InSourceString);

	static void Vector_UnitCartesianToSphericalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          MonoObject** OutValue);

	static LwcType Vector_HeadingAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Vector_CreateOrthonormalBasisImplementation(MonoObject** XAxis, MonoObject** YAxis, MonoObject** ZAxis);

	static bool Vector_PointsAreSameImplementation(const MonoObject* P, const MonoObject* Q);

	static bool Vector_PointsAreNearImplementation(const MonoObject* Point1, const MonoObject* Point2, LwcType Dist);

	static LwcType Vector_PointPlaneDistImplementation(const MonoObject* Point, const MonoObject* PlaneBase,
	                                                   const MonoObject* PlaneNormal);

	static void Vector_PointPlaneProjectByPlaneImplementation(const MonoObject* Point, const MonoObject* Plane,
	                                                          MonoObject** OutValue);

	static void Vector_PointPlaneProjectByPointsImplementation(const MonoObject* Point,
	                                                           const FGarbageCollectionHandle A,
	                                                           const FGarbageCollectionHandle B, const MonoObject* C,
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

	static bool Vector_CoplanarImplementation(const FGarbageCollectionHandle Base1, const MonoObject* Normal1,
	                                          const FGarbageCollectionHandle Base2, const MonoObject* Normal2,
	                                          LwcType ParallelCosineThreshold);

	static LwcType Vector_TripleImplementation(const MonoObject* X, const MonoObject* Y, const MonoObject* Z);

	static void Vector_RadiansToDegreesImplementation(const MonoObject* RadVector, MonoObject** OutValue);

	static void Vector_DegreesToRadiansImplementation(const MonoObject* DegVector, MonoObject** OutValue);
};
