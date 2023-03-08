#pragma once

#include "mono/metadata/object.h"

class FSubclassOfImplementation
{
public:
	static void SubclassOf_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static void SubclassOf_UnRegisterImplementation(const MonoObject* InMonoObject);
};
