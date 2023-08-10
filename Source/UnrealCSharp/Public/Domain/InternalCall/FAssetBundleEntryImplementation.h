#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"

class FAssetBundleEntryImplementation
{
public:
	static bool AssetBundleEntry_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool AssetBundleEntry_EqualityImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B);

	static bool AssetBundleEntry_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);
};
