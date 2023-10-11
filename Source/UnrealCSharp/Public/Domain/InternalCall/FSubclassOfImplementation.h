#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FSubclassOfImplementation
{
public:
	static void SubclassOf_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static bool SubclassOf_IdenticalImplementation(const FGarbageCollectionHandle InA,
	                                               const FGarbageCollectionHandle InB);

	static void SubclassOf_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void SubclassOf_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);
};
