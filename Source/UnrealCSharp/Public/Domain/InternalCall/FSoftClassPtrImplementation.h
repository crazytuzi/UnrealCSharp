#pragma once

#include "mono/metadata/object.h"

class FSoftClassPtrImplementation
{
public:
	static void SoftClassPtr_RegisterImplementation(MonoObject* InMonoObject, const MonoObject* InClass);

	static void SoftClassPtr_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void SoftClassPtr_GetImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
