#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FFunctionImplementation
{
public:
	static void Function_ReflectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoString* InFunctionName, MonoObject** ReturnValue,
	                                              MonoObject** OutValue, MonoArray* InValue);
};
