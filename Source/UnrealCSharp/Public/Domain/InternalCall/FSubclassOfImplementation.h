#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FSubclassOfImplementation
{
public:
	static void SubclassOf_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static void SubclassOf_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void SubclassOf_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);
};
