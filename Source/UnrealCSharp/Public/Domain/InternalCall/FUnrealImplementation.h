#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FUnrealImplementation
{
public:
	static void Unreal_NewObjectImplementation(const FGarbageCollectionHandle Outer,
	                                           const FGarbageCollectionHandle Class, MonoObject* Name,
	                                           MonoObject** OutValue);

	static void Unreal_DuplicateObjectImplementation(const FGarbageCollectionHandle SourceObject,
	                                                 const FGarbageCollectionHandle Outer, MonoObject* Name,
	                                                 MonoObject** OutValue);

	static void Unreal_LoadObjectImplementation(const FGarbageCollectionHandle Outer, MonoString* Name,
	                                            MonoObject** OutValue);

	static void Unreal_LoadClassImplementation(const FGarbageCollectionHandle Outer, MonoString* Name,
	                                           MonoObject** OutValue);
};
