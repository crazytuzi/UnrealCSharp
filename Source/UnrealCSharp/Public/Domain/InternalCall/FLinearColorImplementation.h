#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FLinearColorImplementation
{
public:
	static void LinearColor_ToRGBEImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void LinearColor_FromSRGBColorImplementation(const MonoObject* Color, MonoObject** OutValue);

	static void LinearColor_FromPow22ColorImplementation(const MonoObject* Color, MonoObject** OutValue);

	static float LinearColor_ComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 int32 Index);

	static void LinearColor_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static void LinearColor_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                               MonoObject** OutValue);

	static void LinearColor_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                               MonoObject** OutValue);

	static void LinearColor_MultiplyScalarImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     float Scalar, MonoObject** OutValue);

	static void LinearColor_DivideImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             MonoObject** OutValue);

	static void LinearColor_DivideScalarImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   float Scalar, MonoObject** OutValue);

	static void LinearColor_GetClampedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 float InMin, float InMax, MonoObject** OutValue);

	static bool LinearColor_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool LinearColor_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                 const FGarbageCollectionHandle B);

	static bool LinearColor_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             float Tolerance);

	static void LinearColor_CopyWithNewOpacityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                         float NewOpacicty, MonoObject** OutValue);

	static void LinearColor_MakeFromHSV8Implementation(uint8 H, uint8 S, uint8 V, MonoObject** OutValue);

	static void LinearColor_MakeRandomColorImplementation(MonoObject** OutValue);

	static void LinearColor_MakeFromColorTemperatureImplementation(float Temp, MonoObject** OutValue);

	static float LinearColor_DistImplementation(const FGarbageCollectionHandle V1, const FGarbageCollectionHandle V2);

	static void LinearColor_LinearRGBToHSVImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** OutValue);

	static void LinearColor_HSVToLinearRGBImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** OutValue);

	static void LinearColor_LerpUsingHSVImplementation(const MonoObject* From, const MonoObject* To, float Progress,
	                                                   MonoObject** OutValue);

#if UE_LINEAR_COLOR_QUANTIZE_FLOOR
	static void LinearColor_QuantizeFloorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);
#endif

	static void LinearColor_QuantizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static void LinearColor_QuantizeRoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static void LinearColor_ToFColorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, bool bSRGB,
	                                               MonoObject** OutValue);

	static void LinearColor_DesaturateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 float Desaturation, MonoObject** OutValue);

#if UE_LINEAR_COLOR_COMPUTE_LUMINANCE
	static float LinearColor_ComputeLuminanceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);
#endif

	static float LinearColor_GetMaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool LinearColor_IsAlmostBlackImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static float LinearColor_GetMinImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static float LinearColor_GetLuminanceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void LinearColor_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static bool LinearColor_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject* InSourceString);
};
