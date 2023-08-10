#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FColorImplementation
{
public:
	static uint32 Color_DWColorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Color_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Color_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Color_FromRGBEImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static void Color_FromHexImplementation(MonoObject* HexString, MonoObject** OutValue);

	static void Color_MakeRandomColorImplementation(MonoObject** OutValue);

	static void Color_MakeRedToGreenColorFromScalarImplementation(float Scalar, MonoObject** OutValue);

	static void Color_MakeFromColorTemperatureImplementation(float Temp, MonoObject** OutValue);

	static void Color_WithAlphaImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, uint8 Alpha,
	                                          MonoObject** OutValue);

	static void Color_ReinterpretAsLinearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);

	static void Color_ToHexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      MonoObject** OutValue);

	static void Color_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static bool Color_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject* InSourceString);

	static uint32 Color_ToPackedARGBImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static uint32 Color_ToPackedABGRImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static uint32 Color_ToPackedRGBAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static uint32 Color_ToPackedBGRAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);
};
