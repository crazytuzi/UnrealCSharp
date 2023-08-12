#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FRandomStreamImplementation
{
public:
	static void RandomStream_InitializeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  int32 InSeed);

	static void RandomStream_InitializeNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject* InName);

	static void RandomStream_ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 RandomStream_GetInitialSeedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void RandomStream_GenerateNewSeedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static float RandomStream_GetFractionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static uint32 RandomStream_GetUnsignedIntImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void RandomStream_GetUnitVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject** OutValue);

	static int32 RandomStream_GetCurrentSeedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static float RandomStream_FRandImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 RandomStream_RandHelperImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   int32 A);

	static int32 RandomStream_RandRangeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  int32 Min, int32 Max);

	static float RandomStream_FRandRangeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   float InMin, float InMax);

	static void RandomStream_VRandImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void RandomStream_VRandConeHalfAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          const MonoObject* Dir, float ConeHalfAngleRad,
	                                                          MonoObject** OutValue);

	static void RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Dir,
		float HorizontalConeHalfAngleRad, float VerticalConeHalfAngleRad, MonoObject** OutValue);

	static void RandomStream_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);
};
