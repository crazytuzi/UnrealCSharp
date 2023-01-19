#pragma once

#include "mono/metadata/object-forward.h"

class FRandomStreamImplementation
{
public:
	static void RandomStream_InitializeImplementation(const MonoObject* InMonoObject, int32 InSeed);

	static void RandomStream_InitializeNameImplementation(const MonoObject* InMonoObject, MonoObject* InName);

	static void RandomStream_ResetImplementation(const MonoObject* InMonoObject);

	static int32 RandomStream_GetInitialSeedImplementation(const MonoObject* InMonoObject);

	static void RandomStream_GenerateNewSeedImplementation(const MonoObject* InMonoObject);

	static float RandomStream_GetFractionImplementation(const MonoObject* InMonoObject);

	static uint32 RandomStream_GetUnsignedIntImplementation(const MonoObject* InMonoObject);

	static void RandomStream_GetUnitVectorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static int32 RandomStream_GetCurrentSeedImplementation(const MonoObject* InMonoObject);

	static float RandomStream_FRandImplementation(const MonoObject* InMonoObject);

	static int32 RandomStream_RandHelperImplementation(const MonoObject* InMonoObject, int32 A);

	static int32 RandomStream_RandRangeImplementation(const MonoObject* InMonoObject, int32 Min, int32 Max);

	static float RandomStream_FRandRangeImplementation(const MonoObject* InMonoObject, float InMin, float InMax);

	static void RandomStream_VRandImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void RandomStream_VRandConeHalfAngleImplementation(const MonoObject* InMonoObject, const MonoObject* Dir,
	                                                          float ConeHalfAngleRad, MonoObject** OutValue);

	static void RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
		const MonoObject* InMonoObject, const MonoObject* Dir, float HorizontalConeHalfAngleRad,
		float VerticalConeHalfAngleRad, MonoObject** OutValue);

	static void RandomStream_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
