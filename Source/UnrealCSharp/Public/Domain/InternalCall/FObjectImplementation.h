#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FObjectImplementation
{
public:
	static void Object_StaticClassImplementation(MonoString* InClassName, MonoObject** OutValue);

	static void Object_GetClassImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Object_GetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);

	static void Object_GetWorldImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static bool Object_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Object_IsAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                     const FGarbageCollectionHandle SomeBase);
};
