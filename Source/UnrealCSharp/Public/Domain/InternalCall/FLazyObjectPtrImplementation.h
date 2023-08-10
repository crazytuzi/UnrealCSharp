#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FLazyObjectPtrImplementation
{
public:
	static void LazyObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static void LazyObjectPtr_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void LazyObjectPtr_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);
};
