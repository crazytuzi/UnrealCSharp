#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FMatrixImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static LwcType Matrix_GetMImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, uint32 InRow,
	                                         uint32 InColumn);

	static void Matrix_SetMImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, uint32 InRow,
	                                      uint32 InColumn, LwcType InValue);

	static void Matrix_SetIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Matrix_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static void Matrix_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                     MonoObject** OutValue);

	static void Matrix_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Other, MonoObject** OutValue);

	static bool Matrix_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        LwcType Tolerance);

	static void Matrix_TransformFVector4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* V, MonoObject** OutValue);

	static void Matrix_TransformPositionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* V, MonoObject** OutValue);

	static void Matrix_InverseTransformPositionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          const MonoObject* V, MonoObject** OutValue);

	static void Matrix_TransformVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 const MonoObject* V, MonoObject** OutValue);

	static void Matrix_InverseTransformVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                        const MonoObject* V, MonoObject** OutValue);

	static void Matrix_GetTransposedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static LwcType Matrix_DeterminantImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Matrix_RotDeterminantImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Matrix_InverseFastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void Matrix_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static void Matrix_TransposeAdjointImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static void Matrix_RemoveScalingImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Tolerance);

	static void Matrix_GetMatrixWithoutScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       LwcType Tolerance, MonoObject** OutValue);

	static void Matrix_ExtractScalingImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Tolerance, MonoObject** OutValue);

	static void Matrix_GetScaleVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Tolerance, MonoObject** OutValue);

	static void Matrix_RemoveTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static void Matrix_ConcatTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const MonoObject* Translation, MonoObject** OutValue);

	static bool Matrix_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Matrix_ScaleTranslationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* Scale3D);

	static LwcType Matrix_GetMaximumAxisScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Matrix_ApplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Scale,
	                                            MonoObject** OutValue);

	static void Matrix_GetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void Matrix_GetScaledAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** X, MonoObject** Y, MonoObject** Z);

	static void Matrix_GetUnitAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** X, MonoObject** Y, MonoObject** Z);

	static void Matrix_SetAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 i,
	                                         const MonoObject* Axis);

	static void Matrix_SetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const MonoObject* NewOrigin);

	static void Matrix_SetAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         const MonoObject* Axis0, const MonoObject* Axis1, const MonoObject* Axis2,
	                                         const MonoObject* Origin);

	static void Matrix_GetColumnImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 i,
	                                           MonoObject** OutValue);

	static void Matrix_SetColumnImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 i,
	                                           const MonoObject* Value);

	static void Matrix_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static void Matrix_ToQuatImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static bool Matrix_GetFrustumNearPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** OutValue);

	static bool Matrix_GetFrustumFarPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static bool Matrix_GetFrustumLeftPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** OutValue);

	static bool Matrix_GetFrustumRightPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutValue);

	static bool Matrix_GetFrustumTopPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static bool Matrix_GetFrustumBottomPlaneImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** OutValue);

	static void Matrix_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static uint32 Matrix_ComputeHashImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);
};
