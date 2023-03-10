#pragma once

#include "mono/metadata/object.h"

class FLazyObjectPtrImplementation
{
public:
	static void LazyObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static void LazyObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void LazyObjectPtr_GetImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
