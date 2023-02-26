#pragma once

#include "mono/metadata/object.h"

class FStructImplementation
{
public:
	static void Struct_RegisterImplementation(MonoObject* InMonoObject, MonoString* InStructName);

	static void Struct_UnRegisterImplementation(const MonoObject* InMonoObject);
};
