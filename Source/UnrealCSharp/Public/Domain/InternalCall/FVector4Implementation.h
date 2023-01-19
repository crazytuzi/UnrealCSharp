#pragma once

#include "mono/metadata/object-forward.h"

class FVector4Implementation
{
public:
	static float Vector4_GetComponentImplementation(const MonoObject* InMonoObject, int32 ComponentIndex);

	static void Vector4_SetComponentImplementation(const MonoObject* InMonoObject, int32 ComponentIndex, float InValue);

	static void Vector4_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_MultiplyScaleImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static void Vector4_DivideScaleImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static void Vector4_DivideImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static float Vector4_Dot3Implementation(const MonoObject* A, const MonoObject* B);

	static float Vector4_Dot4Implementation(const MonoObject* A, const MonoObject* B);

	static bool Vector4_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector4_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void Vector4_CrossProductImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static float Vector4_ComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static bool Vector4_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static bool Vector4_IsUnit3Implementation(const MonoObject* InMonoObject, float LengthSquaredTolerance);

	static void Vector4_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Vector4_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static void Vector4_GetSafeNormalImplementation(const MonoObject* InMonoObject, float Tolerance,
	                                                MonoObject** OutValue);

	static void Vector4_GetUnsafeNormal3Implementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_ToOrientationRotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_ToOrientationQuatImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_RotationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_SetImplementation(const MonoObject* InMonoObject, float InX, float InY, float InZ, float InW);

	static float Vector4_Size3Implementation(const MonoObject* InMonoObject);

	static float Vector4_SizeSquared3Implementation(const MonoObject* InMonoObject);

	static float Vector4_SizeImplementation(const MonoObject* InMonoObject);

	static float Vector4_SizeSquaredImplementation(const MonoObject* InMonoObject);

	static bool Vector4_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static bool Vector4_IsNearlyZero3Implementation(const MonoObject* InMonoObject, float Tolerance);

	static void Vector4_Reflect3Implementation(const MonoObject* InMonoObject, const MonoObject* Normal,
	                                           MonoObject** OutValue);

	static void Vector4_FindBestAxisVectors3Implementation(const MonoObject* InMonoObject, MonoObject** Axis1,
	                                                       MonoObject** Axis2);
};
