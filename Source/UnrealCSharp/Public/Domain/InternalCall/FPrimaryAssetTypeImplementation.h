#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FPrimaryAssetTypeImplementation
{
public:
	static void PrimaryAssetType_GetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static bool PrimaryAssetType_EqualityImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B);

	static bool PrimaryAssetType_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);

	static bool PrimaryAssetType_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void PrimaryAssetType_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** OutValue);
};
