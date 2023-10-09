#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FGuidImplementation
{
public:
	static bool Guid_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Guid_GreaterThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static uint32 Guid_GetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              int32 Index);

	static void Guid_SetComponentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 Index,
	                                            uint32 InValue);

	static void Guid_LexToStringImplementation(const MonoObject* Value, MonoObject** OutValue);

	static void Guid_InvalidateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Guid_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Guid_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Guid_NewGuidImplementation(MonoObject** OutValue);

	static bool Guid_ParseImplementation(MonoObject* GuidString, MonoObject** OutGuid);
};
