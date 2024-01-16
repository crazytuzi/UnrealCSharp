﻿#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FSoftObjectPtrImplementation
{
public:
	static void SoftObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static bool SoftObjectPtr_IdenticalImplementation(const FGarbageCollectionHandle InA,
	                                                  const FGarbageCollectionHandle InB);

	static void SoftObjectPtr_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void SoftObjectPtr_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void SoftObjectPtr_LoadSynchronousImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                        MonoObject** OutValue);
};
