#pragma once

#include "mono/metadata/object-forward.h"

class FSoftClassPathImplementation
{
public:
	static void SoftClassPath_GetOrCreateIDForObjectImplementation(const MonoObject* InMonoObject,
	                                                               MonoObject** OutValue);
};
