#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FRotatorImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Rotator_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                      MonoObject** OutValue);

	static void Rotator_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                           MonoObject** OutValue);

	static void Rotator_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Scale,
	                                           MonoObject** OutValue);

	static bool Rotator_IsNearlyZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               LwcType Tolerance);

	static bool Rotator_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Rotator_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                         LwcType Tolerance);

	static void Rotator_AddDeltaImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           LwcType DeltaPitch, LwcType DeltaYaw, LwcType DeltaRoll,
	                                           MonoObject** OutValue);

	static void Rotator_GetInverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void Rotator_GridSnapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const MonoObject* RotGrid, MonoObject** OutValue);

	static void Rotator_VectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static void Rotator_QuaternionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void Rotator_EulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Rotator_RotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const MonoObject* V, MonoObject** OutValue);

	static void Rotator_UnrotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 const MonoObject* V, MonoObject** OutValue);

	static void Rotator_ClampImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Rotator_GetNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static void Rotator_GetDenormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static void Rotator_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Rotator_GetWindingAndRemainderImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                         MonoObject** Winding, MonoObject** Remainder);

	static LwcType Rotator_GetManhattanDistanceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          const MonoObject* Rotator);

	static void Rotator_GetEquivalentRotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** OutValue);

	static void Rotator_SetClosestToMeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void Rotator_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void Rotator_ToCompactStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static bool Rotator_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject* InSourceString);

	static bool Rotator_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Rotator_ClampAxisImplementation(LwcType Angle);

	static LwcType Rotator_NormalizeAxisImplementation(LwcType Angle);

	static uint8 Rotator_CompressAxisToByteImplementation(LwcType Angle);

	static LwcType Rotator_DecompressAxisFromByteImplementation(uint8 Angle);

	static uint16 Rotator_CompressAxisToShortImplementation(LwcType Angle);

	static LwcType Rotator_DecompressAxisFromShortImplementation(uint16 Angle);

	static void Rotator_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue);
};
