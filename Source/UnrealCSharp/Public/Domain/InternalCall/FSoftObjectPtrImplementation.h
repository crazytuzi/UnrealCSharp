#pragma once

#include "mono/metadata/object.h"

class FSoftObjectPtrImplementation
{
public:
	static void SoftObjectPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InObject);

	static void SoftObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void SoftObjectPtr_GetImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
