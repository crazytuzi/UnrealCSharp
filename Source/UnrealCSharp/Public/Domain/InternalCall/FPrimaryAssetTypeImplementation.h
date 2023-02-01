#pragma once

#include "mono/metadata/object-forward.h"

class FPrimaryAssetTypeImplementation
{
public:
	static void PrimaryAssetType_GetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool PrimaryAssetType_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool PrimaryAssetType_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool PrimaryAssetType_IsValidImplementation(const MonoObject* InMonoObject);

	static void PrimaryAssetType_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
