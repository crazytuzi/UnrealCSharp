#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FAssetBundleDataImplementation
{
public:
	static bool AssetBundleData_EqualityImplementation(const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static bool AssetBundleData_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                     const FGarbageCollectionHandle B);

	static void AssetBundleData_FindEntryImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject* SearchName, MonoObject** OutValue);

	static void AssetBundleData_AddBundleAssetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                         MonoObject* BundleName, const MonoObject* AssetPath);

	static void AssetBundleData_ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void AssetBundleData_ToDebugStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                        MonoObject** OutValue);
};
