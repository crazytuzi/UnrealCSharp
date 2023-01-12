#pragma once

#include "mono/metadata/object-forward.h"

class FMatrixImplementation
{
public:
	static float Matrix_GetMImplementation(const MonoObject* InMonoObject, uint32 InRow, uint32 InColumn);

	static void Matrix_SetMImplementation(const MonoObject* InMonoObject, uint32 InRow, uint32 InColumn, float InValue);

	static void Matrix_SetIdentityImplementation(const MonoObject* InMonoObject);

	static void Matrix_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Matrix_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Matrix_MultiplyScaleImplementation(const MonoObject* InMonoObject, float Other, MonoObject** OutValue);

	static bool Matrix_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Matrix_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Matrix_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void Matrix_TransformFVector4Implementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                   MonoObject** OutValue);

	static void Matrix_TransformPositionImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                   MonoObject** OutValue);

	static void Matrix_InverseTransformPositionImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                          MonoObject** OutValue);

	static void Matrix_TransformVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                 MonoObject** OutValue);

	static void Matrix_InverseTransformVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                        MonoObject** OutValue);

	static void Matrix_GetTransposedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static float Matrix_DeterminantImplementation(const MonoObject* InMonoObject);

	static float Matrix_RotDeterminantImplementation(const MonoObject* InMonoObject);

	static void Matrix_InverseFastImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_TransposeAdjointImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_RemoveScalingImplementation(const MonoObject* InMonoObject, float Tolerance);

	static void Matrix_GetMatrixWithoutScaleImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                                       MonoObject** OutValue);

	static void Matrix_ExtractScalingImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                                MonoObject** OutValue);

	static void Matrix_GetScaleVectorImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                                MonoObject** OutValue);

	static void Matrix_RemoveTranslationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_ConcatTranslationImplementation(const MonoObject* InMonoObject, const MonoObject* Translation,
	                                                   MonoObject** OutValue);

	static bool Matrix_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static void Matrix_ScaleTranslationImplementation(const MonoObject* InMonoObject, const MonoObject* Scale3D);

	static float Matrix_GetMaximumAxisScaleImplementation(const MonoObject* InMonoObject);

	static void Matrix_ApplyScaleImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static void Matrix_GetOriginImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_GetScaledAxesImplementation(const MonoObject* InMonoObject, MonoObject** X, MonoObject** Y,
	                                               MonoObject** Z);

	static void Matrix_GetUnitAxesImplementation(const MonoObject* InMonoObject, MonoObject** X, MonoObject** Y,
	                                             MonoObject** Z);

	static void Matrix_SetAxisImplementation(const MonoObject* InMonoObject, int32 i, const MonoObject* Axis);

	static void Matrix_SetOriginImplementation(const MonoObject* InMonoObject, const MonoObject* NewOrigin);

	static void Matrix_SetAxesImplementation(const MonoObject* InMonoObject, const MonoObject* Axis0,
	                                         const MonoObject* Axis1, const MonoObject* Axis2,
	                                         const MonoObject* Origin);

	static void Matrix_GetColumnImplementation(const MonoObject* InMonoObject, int32 i, MonoObject** OutValue);

	static void Matrix_SetColumnImplementation(const MonoObject* InMonoObject, int32 i, const MonoObject* Value);

	static void Matrix_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_ToQuatImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumNearPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumFarPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumLeftPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumRightPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumTopPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Matrix_GetFrustumBottomPlaneImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Matrix_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static uint32 Matrix_ComputeHashImplementation(const MonoObject* InMonoObject);
};
