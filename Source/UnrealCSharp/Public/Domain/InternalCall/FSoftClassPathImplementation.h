#pragma once

#include "mono/metadata/object-forward.h"

class FSoftClassPathImplementation
{
public:
	static void SoftClassPath_GetOrCreateIDForClassImplementation(const MonoObject* InMonoObject,
	                                                              MonoObject** OutValue);
};
