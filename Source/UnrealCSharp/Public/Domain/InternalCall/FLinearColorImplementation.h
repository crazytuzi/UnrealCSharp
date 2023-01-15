#pragma once

#include "mono/metadata/object-forward.h"

class FLinearColorImplementation
{
public:
	static void LinearColor_ToRGBEImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void LinearColor_FromSRGBColorImplementation(const MonoObject* Color, MonoObject** OutValue);

	static void LinearColor_FromPow22ColorImplementation(const MonoObject* Color, MonoObject** OutValue);

	static float LinearColor_ComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static void LinearColor_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void LinearColor_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void LinearColor_MultiplyImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void LinearColor_MultiplyScalarImplementation(const MonoObject* InMonoObject, float Scalar,
	                                                     MonoObject** OutValue);

	static void LinearColor_DivideImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void LinearColor_DivideScalarImplementation(const MonoObject* InMonoObject, float Scalar,
	                                                   MonoObject** OutValue);

	static void LinearColor_GetClampedImplementation(const MonoObject* InMonoObject, float InMin, float InMax,
	                                                 MonoObject** OutValue);

	static bool LinearColor_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool LinearColor_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool LinearColor_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static void LinearColor_CopyWithNewOpacityImplementation(const MonoObject* InMonoObject, float NewOpacicty,
	                                                         MonoObject** OutValue);

	static void LinearColor_MakeFromHSV8Implementation(uint8 H, uint8 S, uint8 V, MonoObject** OutValue);

	static void LinearColor_MakeRandomColorImplementation(MonoObject** OutValue);

	static void LinearColor_MakeFromColorTemperatureImplementation(float Temp, MonoObject** OutValue);

	static float LinearColor_DistImplementation(const MonoObject* V1, const MonoObject* V2);

	static void LinearColor_LinearRGBToHSVImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void LinearColor_HSVToLinearRGBImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void LinearColor_LerpUsingHSVImplementation(const MonoObject* From, const MonoObject* To, float Progress,
	                                                   MonoObject** OutValue);

	static void LinearColor_QuantizeImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void LinearColor_QuantizeRoundImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void LinearColor_ToFColorImplementation(const MonoObject* InMonoObject, bool bSRGB, MonoObject** OutValue);

	static void LinearColor_DesaturateImplementation(const MonoObject* InMonoObject, float Desaturation,
	                                                 MonoObject** OutValue);

	static float LinearColor_ComputeLuminanceImplementation(const MonoObject* InMonoObject);

	static float LinearColor_GetMaxImplementation(const MonoObject* InMonoObject);

	static bool LinearColor_IsAlmostBlackImplementation(const MonoObject* InMonoObject);

	static float LinearColor_GetMinImplementation(const MonoObject* InMonoObject);

	static float LinearColor_GetLuminanceImplementation(const MonoObject* InMonoObject);

	static void LinearColor_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool LinearColor_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);
};
