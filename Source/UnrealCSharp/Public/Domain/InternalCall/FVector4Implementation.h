#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FVector4Implementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static LwcType Vector4_GetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  int32 ComponentIndex);

	static void Vector4_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               int32 ComponentIndex, LwcType InValue);

	static void Vector4_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Vector4_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                      MonoObject** OutValue);

	static void Vector4_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                           MonoObject** OutValue);

	static void Vector4_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Scale, MonoObject** OutValue);

	static void Vector4_DivideScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              LwcType Scale, MonoObject** OutValue);

	static void Vector4_DivideImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                         MonoObject** OutValue);

	static void Vector4_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                           MonoObject** OutValue);

	static LwcType Vector4_Dot3Implementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static LwcType Vector4_Dot4Implementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Vector4_CrossProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                               MonoObject** OutValue);

	static LwcType Vector4_ComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               int32 Index);

	static bool Vector4_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                         LwcType Tolerance);

	static bool Vector4_IsUnit3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          LwcType LengthSquaredTolerance);

	static void Vector4_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static bool Vector4_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject* InSourceString);

	static void Vector4_GetSafeNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Tolerance, MonoObject** OutValue);

	static void Vector4_GetUnsafeNormal3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static void Vector4_ToOrientationRotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** OutValue);

	static void Vector4_ToOrientationQuatImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static void Vector4_RotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void Vector4_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType InX,
	                                      LwcType InY, LwcType InZ, LwcType InW);

	static LwcType Vector4_Size3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector4_SizeSquared3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector4_SizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector4_SizeSquaredImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector4_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Vector4_IsNearlyZero3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Tolerance);

	static void Vector4_Reflect3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const MonoObject* Normal, MonoObject** OutValue);

	static void Vector4_FindBestAxisVectors3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** Axis1, MonoObject** Axis2);
};
