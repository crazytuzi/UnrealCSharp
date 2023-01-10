#pragma once

#include "mono/metadata/object-forward.h"

class FRotatorImplementation
{
public:
	static void Rotator_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Rotator_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Rotator_MultiplyImplementation(const MonoObject* InMonoObject, float Scale, MonoObject** OutValue);

	static bool Rotator_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Rotator_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Rotator_IsNearlyZeroImplementation(const MonoObject* InMonoObject, float Tolerance);

	static bool Rotator_IsZeroImplementation(const MonoObject* InMonoObject);

	static bool Rotator_EqualsImplementation(const MonoObject* A, const MonoObject* B, float Tolerance);

	static void Rotator_AddDeltaImplementation(const MonoObject* InMonoObject, float DeltaPitch, float DeltaYaw,
	                                           float DeltaRoll, MonoObject** OutValue);

	static void Rotator_GetInverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_GridSnapImplementation(const MonoObject* InMonoObject, const MonoObject* RotGrid,
	                                           MonoObject** OutValue);

	static void Rotator_VectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_QuaternionImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_EulerImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_RotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                               MonoObject** OutValue);

	static void Rotator_UnrotateVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
	                                                 MonoObject** OutValue);

	static void Rotator_ClampImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_GetNormalizedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_GetDenormalizedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_NormalizeImplementation(const MonoObject* InMonoObject);

	static void Rotator_GetWindingAndRemainderImplementation(const MonoObject* InMonoObject, MonoObject** Winding,
	                                                         MonoObject** Remainder);

	static float Rotator_GetManhattanDistanceImplementation(const MonoObject* InMonoObject, const MonoObject* Rotator);

	static void Rotator_GetEquivalentRotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_SetClosestToMeImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Rotator_ToCompactStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Rotator_InitFromStringImplementation(const MonoObject* InMonoObject, MonoObject* InSourceString);

	static bool Rotator_ContainsNaNImplementation(const MonoObject* InMonoObject);

	static float Rotator_ClampAxisImplementation(float Angle);

	static float Rotator_NormalizeAxisImplementation(float Angle);

	static uint8 Rotator_CompressAxisToByteImplementation(float Angle);

	static float Rotator_DecompressAxisFromByteImplementation(uint8 Angle);

	static uint16 Rotator_CompressAxisToShortImplementation(float Angle);

	static float Rotator_DecompressAxisFromShortImplementation(uint16 Angle);

	static void Rotator_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue);
};
