#pragma once

#include "mono/metadata/object.h"

class FUnrealImplementation
{
public:
	static void Unreal_NewObjectImplementation(const MonoObject* Outer, const MonoObject* Class, MonoObject* Name,
	                                           MonoObject** OutValue);

	static void Unreal_NewObjectWithClassNameImplementation(const MonoObject* Outer, MonoString* Class,
	                                                        MonoObject* Name, MonoObject** OutValue);
};
