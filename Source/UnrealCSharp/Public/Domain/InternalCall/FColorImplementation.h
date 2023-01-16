#pragma once

#include "mono/metadata/object-forward.h"

class FColorImplementation
{
public:
	static uint32 Color_DWColorImplementation(const MonoObject* InMonoObject);

	static bool Color_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Color_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void Color_FromRGBEImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Color_FromHexImplementation(MonoObject* HexString, MonoObject** OutValue);

	static void Color_MakeRandomColorImplementation(MonoObject** OutValue);

	static void Color_MakeRedToGreenColorFromScalarImplementation(float Scalar, MonoObject** OutValue);

	static void Color_MakeFromColorTemperatureImplementation(float Temp, MonoObject** OutValue);

	static void Color_WithAlphaImplementation(const MonoObject* InMonoObject, uint8 Alpha, MonoObject** OutValue);

	static void Color_ReinterpretAsLinearImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Color_ToHexImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Color_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Color_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static uint32 Color_ToPackedARGBImplementation(const MonoObject* InMonoObject);

	static uint32 Color_ToPackedABGRImplementation(const MonoObject* InMonoObject);

	static uint32 Color_ToPackedRGBAImplementation(const MonoObject* InMonoObject);

	static uint32 Color_ToPackedBGRAImplementation(const MonoObject* InMonoObject);
};
