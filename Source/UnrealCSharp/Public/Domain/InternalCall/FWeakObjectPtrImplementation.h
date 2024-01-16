#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FWeakObjectPtrImplementation
{
public:
	static void WeakObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static bool WeakObjectPtr_IdenticalImplementation(const FGarbageCollectionHandle InA,
	                                                  const FGarbageCollectionHandle InB);

	static void WeakObjectPtr_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void WeakObjectPtr_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);
};
