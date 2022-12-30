#pragma once

#include "mono/metadata/object.h"

class FObjectImplementation
{
public:
	static void Object_StaticClassImplementation(const UTF16CHAR* InClassName, MonoObject** OutValue);

	static void Object_GetClassImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Object_GetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
