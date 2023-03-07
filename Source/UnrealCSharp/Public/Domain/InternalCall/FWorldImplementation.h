#pragma once

#include "mono/metadata/object.h"

class FWorldImplementation
{
public:
	static void World_SpawnActorImplementation(const MonoObject* InMonoObject, const MonoObject* Class,
	                                           const MonoObject* Transform, MonoObject** OutValue);
};
