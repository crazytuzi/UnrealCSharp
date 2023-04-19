#pragma once

#include "mono/metadata/object.h"

class FDelegateImplementation
{
public:
	static void Delegate_RegisterImplementation(MonoObject* InMonoObject);

	static void Delegate_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void Delegate_BindImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate);

	static bool Delegate_IsBoundImplementation(const MonoObject* InMonoObject);

	static void Delegate_UnBindImplementation(const MonoObject* InMonoObject);

	static void Delegate_ClearImplementation(const MonoObject* InMonoObject);

	static void Delegate_ExecuteImplementation(const MonoObject* InMonoObject, MonoObject** ReturnValue,
	                                           MonoObject** OutValue, MonoArray* InValue);
};
