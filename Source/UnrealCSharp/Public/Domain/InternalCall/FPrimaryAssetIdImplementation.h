#pragma once

#include "mono/metadata/object-forward.h"

class FPrimaryAssetIdImplementation
{
public:
	static void PrimaryAssetId_ParseTypeAndNameNameImplementation(MonoObject* TypeAndName, MonoObject** OutValue);

	static void PrimaryAssetId_ParseTypeAndNameStringImplementation(MonoObject* TypeAndName, MonoObject** OutValue);

	static bool PrimaryAssetId_IsValidImplementation(const MonoObject* InMonoObject);

	static void PrimaryAssetId_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void PrimaryAssetId_FromStringImplementation(MonoObject* String, MonoObject** OutValue);

	static bool PrimaryAssetId_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool PrimaryAssetId_InequalityImplementation(const MonoObject* A, const MonoObject* B);
};
