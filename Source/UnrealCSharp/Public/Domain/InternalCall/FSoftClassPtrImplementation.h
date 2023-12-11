#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FSoftClassPtrImplementation
{
public:
	static void SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static bool SoftClassPtr_IdenticalImplementation(const FGarbageCollectionHandle InA,
	                                                 const FGarbageCollectionHandle InB);

	static void SoftClassPtr_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void SoftClassPtr_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void SoftClassPtr_LoadSynchronousImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** OutValue);
};
