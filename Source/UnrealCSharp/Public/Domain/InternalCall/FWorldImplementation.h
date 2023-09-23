#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FWorldImplementation
{
public:
	static void World_SpawnActorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const FGarbageCollectionHandle InClass, const MonoObject* InTransform,
	                                           const FGarbageCollectionHandle InOwner,
	                                           const FGarbageCollectionHandle InInstigator,
	                                           uint8 InCollisionHandlingOverride, MonoObject** OutValue);
};
