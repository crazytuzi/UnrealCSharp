#pragma once

#include "mono/metadata/object.h"

class FMulticastDelegateImplementation
{
public:
	static bool MulticastDelegate_IsBoundImplementation(const void* InAddress);

	static bool MulticastDelegate_ContainsImplementation(const void* InAddress, MonoObject* InDelegate);

	static void MulticastDelegate_AddImplementation(const void* InAddress, MonoObject* InDelegate);

	static void MulticastDelegate_AddUniqueImplementation(const void* InAddress, MonoObject* InDelegate);

	static void MulticastDelegate_RemoveImplementation(const void* InAddress, MonoObject* InDelegate);

	static void MulticastDelegate_RemoveAllImplementation(const void* InAddress, MonoObject* InMonoObject);

	static void MulticastDelegate_ClearImplementation(const void* InAddress);

	static void MulticastDelegate_BroadcastImplementation(const void* InAddress, MonoObject** OutValue,
	                                                      MonoArray* InValue);
};
