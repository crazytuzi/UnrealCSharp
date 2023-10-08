#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FPrimaryAssetIdImplementation
{
public:
	static void PrimaryAssetId_ParseTypeAndNameNameImplementation(MonoObject* TypeAndName, MonoObject** OutValue);

	static void PrimaryAssetId_ParseTypeAndNameStringImplementation(MonoObject* TypeAndName, MonoObject** OutValue);

	static bool PrimaryAssetId_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void PrimaryAssetId_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static void PrimaryAssetId_FromStringImplementation(MonoObject* String, MonoObject** OutValue);
};
