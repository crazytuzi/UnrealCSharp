#pragma once

#include "UEVersion.h"
#include "mono/metadata/object-forward.h"

class FVector4Implementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static LwcType Vector4_GetComponentImplementation(const MonoObject* InMonoObject, int32 ComponentIndex);

	static void Vector4_SetComponentImplementation(const MonoObject* InMonoObject, int32 ComponentIndex,
	                                               LwcType InValue);

	static void Vector4_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_MultiplyScaleImplementation(const MonoObject* InMonoObject, LwcType Scale,
	                                                MonoObject** OutValue);

	static void Vector4_DivideScaleImplementation(const MonoObject* InMonoObject, LwcType Scale, MonoObject** OutValue);

	static void Vector4_DivideImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Vector4_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static LwcType Vector4_Dot3Implementation(const MonoObject* A, const MonoObject* B);

	static LwcType Vector4_Dot4Implementation(const MonoObject* A, const MonoObject* B);

	static bool Vector4_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Vector4_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void Vector4_CrossProductImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static LwcType Vector4_ComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static bool Vector4_EqualsImplementation(const MonoObject* A, const MonoObject* B, LwcType Tolerance);

	static bool Vector4_IsUnit3Implementation(const MonoObject* InMonoObject, LwcType LengthSquaredTolerance);

	static void Vector4_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Vector4_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static void Vector4_GetSafeNormalImplementation(const MonoObject* InMonoObject, LwcType Tolerance,
	                                                MonoObject** OutValue);

	static void Vector4_GetUnsafeNormal3Implementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_ToOrientationRotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_ToOrientationQuatImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_RotationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Vector4_SetImplementation(const MonoObject* InMonoObject, LwcType InX, LwcType InY, LwcType InZ,
	                                      LwcType InW);

	static LwcType Vector4_Size3Implementation(const MonoObject* InMonoObject);

	static LwcType Vector4_SizeSquared3Implementation(const MonoObject* InMonoObject);

	static LwcType Vector4_SizeImplementation(const MonoObject* InMonoObject);

	static LwcType Vector4_SizeSquaredImplementation(const MonoObject* InMonoObject);

	static bool Vector4_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static bool Vector4_IsNearlyZero3Implementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static void Vector4_Reflect3Implementation(const MonoObject* InMonoObject, const MonoObject* Normal,
	                                           MonoObject** OutValue);

	static void Vector4_FindBestAxisVectors3Implementation(const MonoObject* InMonoObject, MonoObject** Axis1,
	                                                       MonoObject** Axis2);
};
