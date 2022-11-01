#pragma once

#include "mono/metadata/object-forward.h"

class FStructImplementation
{
public:
	static void RegisterStructImplementation(MonoObject InMonoObject, const UTF16CHAR* InStructName);

	static void UnRegisterStructImplementation(MonoObject InMonoObject);
};
