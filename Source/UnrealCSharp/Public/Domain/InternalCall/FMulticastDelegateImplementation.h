#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FMulticastDelegateImplementation
{
public:
	static void MulticastDelegate_RegisterImplementation(MonoObject* InMonoObject);

	static void MulticastDelegate_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool MulticastDelegate_IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool MulticastDelegate_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject* InDelegate);

	static void MulticastDelegate_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject* InDelegate);

	static void MulticastDelegate_AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject* InDelegate);

	static void MulticastDelegate_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject* InDelegate);

	static void MulticastDelegate_RemoveAllImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject* InObject);

	static void MulticastDelegate_ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void MulticastDelegate_BroadcastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutValue, MonoArray* InValue);
};
