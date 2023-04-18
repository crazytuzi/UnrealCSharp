#pragma once

#include "mono/metadata/object.h"

class FObjectImplementation
{
public:
	static void Object_StaticClassImplementation(MonoString* InClassName, MonoObject** OutValue);

	static void Object_GetClassImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Object_GetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Object_GetWorldImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static bool Object_IsValidImplementation(const MonoObject* InMonoObject);
};
