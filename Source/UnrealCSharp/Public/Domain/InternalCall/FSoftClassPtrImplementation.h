#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FSoftClassPtrImplementation
{
public:
	static void SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static void SoftClassPtr_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void SoftClassPtr_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);
};
