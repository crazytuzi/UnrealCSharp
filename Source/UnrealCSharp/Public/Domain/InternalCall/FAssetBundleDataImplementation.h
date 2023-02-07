#pragma once

#include "mono/metadata/object-forward.h"

class FAssetBundleDataImplementation
{
public:
	static bool AssetBundleData_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool AssetBundleData_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void AssetBundleData_FindEntryImplementation(const MonoObject* InMonoObject, MonoObject* SearchName,
	                                                    MonoObject** OutValue);

	static void AssetBundleData_AddBundleAssetImplementation(const MonoObject* InMonoObject, MonoObject* BundleName,
	                                                         const MonoObject* AssetPath);

	static void AssetBundleData_ResetImplementation(const MonoObject* InMonoObject);

	static void AssetBundleData_ToDebugStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
