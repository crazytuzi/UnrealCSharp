#pragma once

#include "mono/metadata/object-forward.h"

class FClassImplementation
{
public:
	static void Class_GetDefaultObjectImplementation(const MonoObject* InMonoObject, bool bCreateIfNeeded,
	                                                 MonoObject** OutValue);
};
