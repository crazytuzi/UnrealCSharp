#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FVector2DImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Vector2D_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                       MonoObject** OutValue);

	static void Vector2D_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                            MonoObject** OutValue);

	static void Vector2D_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 LwcType Scale, MonoObject** OutValue);

	static void Vector2D_DivideScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Scale, MonoObject** OutValue);

	static void Vector2D_AddAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType A,
	                                        MonoObject** OutValue);

	static void Vector2D_SubtractAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType A,
	                                             MonoObject** OutValue);

	static void Vector2D_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                            MonoObject** OutValue);

	static void Vector2D_DivideImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static LwcType
	Vector2D_DotProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static LwcType Vector2D_CrossProductImplementation(const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static bool Vector2D_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector2D_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector2D_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector2D_GreaterThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Vector2D_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static bool Vector2D_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);

	static void Vector2D_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static LwcType Vector2D_GetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   int32 Index);

	static void Vector2D_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                int32 Index, LwcType InValue);

	static LwcType Vector2D_ComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                int32 Index);

	static LwcType Vector2D_DistSquaredImplementation(const FGarbageCollectionHandle A,
	                                                  const FGarbageCollectionHandle B);

	static LwcType Vector2D_DistanceImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Vector2D_MaxImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                       MonoObject** OutValue);

	static void Vector2D_MinImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                       MonoObject** OutValue);

	static bool Vector2D_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          LwcType Tolerance);

	static void Vector2D_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType InX,
	                                       LwcType InY);

	static LwcType Vector2D_GetMaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector2D_GetAbsMaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector2D_GetMinImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector2D_SizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Vector2D_SizeSquaredImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Vector2D_GetRotatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              LwcType AngleDeg, MonoObject** OutValue);

	static void Vector2D_GetSafeNormalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 LwcType Tolerance, MonoObject** OutValue);

	static void Vector2D_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType Tolerance);

	static bool Vector2D_IsNearlyZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                LwcType Tolerance);

	static void Vector2D_IntPointImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void Vector2D_RoundToVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void Vector2D_ClampAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType MinAxisVal, LwcType MaxAxisVal, MonoObject** OutValue);

	static void Vector2D_GetSignVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void Vector2D_GetAbsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Vector2D_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static bool Vector2D_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject* InSourceString);

	static bool Vector2D_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Vector2D_SphericalToUnitCartesianImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);
};
