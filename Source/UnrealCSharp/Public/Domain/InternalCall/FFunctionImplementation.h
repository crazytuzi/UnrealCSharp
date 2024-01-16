﻿#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FFunctionImplementation
{
public:
	static void Function_ReflectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const uint32 InFunctionHash, MonoObject** ReturnValue,
	                                              MonoObject** OutValue, MonoArray* InValue);
};
