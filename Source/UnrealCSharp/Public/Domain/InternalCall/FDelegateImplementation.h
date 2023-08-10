#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FDelegateImplementation
{
public:
	static void Delegate_RegisterImplementation(MonoObject* InMonoObject);

	static void Delegate_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Delegate_BindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject* InDelegate);

	static bool Delegate_IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Delegate_UnBindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Delegate_ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Delegate_ExecuteImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue);
};
