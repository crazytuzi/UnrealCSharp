#pragma once

#include "mono/metadata/object-forward.h"

class FAssetBundleEntryImplementation
{
public:
	static bool AssetBundleEntry_IsValidImplementation(const MonoObject* InMonoObject);

	static bool AssetBundleEntry_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool AssetBundleEntry_InequalityImplementation(const MonoObject* A, const MonoObject* B);
};
