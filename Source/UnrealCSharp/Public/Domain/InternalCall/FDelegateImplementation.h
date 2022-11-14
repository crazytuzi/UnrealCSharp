#pragma once

#include "mono/metadata/object.h"

class FDelegateImplementation
{
public:
	static void Delegate_BindImplementation(const void* InAddress, MonoObject* InDelegate);

	static bool Delegate_IsBoundImplementation(const void* InAddress);

	static void Delegate_UnBindImplementation(const void* InAddress);

	static void Delegate_ClearImplementation(const void* InAddress);

	static void Delegate_ExecuteImplementation(const void* InAddress, MonoObject** ReturnValue, MonoObject** OutValue,
	                                           MonoArray* InValue);
};
