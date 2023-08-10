#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FWorldImplementation
{
public:
	static void World_SpawnActorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const FGarbageCollectionHandle Class, const MonoObject* Transform,
	                                           MonoObject** OutValue);
};
