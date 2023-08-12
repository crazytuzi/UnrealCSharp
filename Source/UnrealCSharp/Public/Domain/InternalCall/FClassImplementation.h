#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FClassImplementation
{
public:
	static void Class_GetDefaultObjectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 bool bCreateIfNeeded, MonoObject** OutValue);
};
