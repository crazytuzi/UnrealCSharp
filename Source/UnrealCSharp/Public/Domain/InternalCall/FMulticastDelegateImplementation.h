#pragma once

#include "mono/metadata/object.h"

class FMulticastDelegateImplementation
{
public:
	static bool MulticastDelegate_IsBoundImplementation(const MonoObject* InMonoObject);

	static bool MulticastDelegate_ContainsImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate);

	static void MulticastDelegate_AddImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate);

	static void MulticastDelegate_AddUniqueImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate);

	static void MulticastDelegate_RemoveImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate);

	static void MulticastDelegate_RemoveAllImplementation(const MonoObject* InMonoObject, MonoObject* InObject);

	static void MulticastDelegate_ClearImplementation(const MonoObject* InMonoObject);

	static void MulticastDelegate_BroadcastImplementation(const MonoObject* InMonoObject, MonoObject** OutValue,
	                                                      MonoArray* InValue);
};
