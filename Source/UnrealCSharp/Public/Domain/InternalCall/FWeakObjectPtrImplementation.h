#pragma once

#include "mono/metadata/object.h"

class FWeakObjectPtrImplementation
{
public:
	static void WeakObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static void WeakObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void WeakObjectPtr_GetImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
