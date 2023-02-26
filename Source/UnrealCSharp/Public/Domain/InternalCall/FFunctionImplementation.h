#pragma once

#include "mono/metadata/object.h"

class FFunctionImplementation
{
public:
	static void Function_ReflectionImplementation(const MonoObject* InMonoObject, MonoString* InFunctionName,
	                                              MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue);
};
