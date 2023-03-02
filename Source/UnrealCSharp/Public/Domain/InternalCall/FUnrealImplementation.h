#pragma once

#include "mono/metadata/object.h"

class FUnrealImplementation
{
public:
	static void Unreal_NewObjectImplementation(const MonoObject* Outer, const MonoObject* Class, MonoObject* Name,
	                                           MonoObject** OutValue);

	static void Unreal_DuplicateObjectImplementation(const MonoObject* SourceObject, const MonoObject* Outer,
	                                                 MonoObject* Name, MonoObject** OutValue);

	static void Unreal_LoadObjectImplementation(const MonoObject* Outer, MonoString* Name, MonoObject** OutValue);

	static void Unreal_LoadClassImplementation(const MonoObject* Outer, MonoString* Name, MonoObject** OutValue);
};
