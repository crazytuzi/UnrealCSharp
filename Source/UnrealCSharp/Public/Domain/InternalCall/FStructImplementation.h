#pragma once

#include "mono/metadata/object-forward.h"

class FStructImplementation
{
public:
	static void Struct_RegisterImplementation(MonoObject* InMonoObject, const UTF16CHAR* InStructName);

	static void Struct_UnRegisterImplementation(const MonoObject* InMonoObject);
};
