#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FSetImplementation
{
public:
	static void Set_RegisterImplementation(MonoObject* InMonoObject);

	static void Set_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Set_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                    int32 InExpectedNumElements);

	static int32 Set_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Set_GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Set_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InValue);

	static int32 Set_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      MonoObject* InValue);

	static bool Set_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                       MonoObject* InValue);

	static bool Set_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex);

	static void Set_GetEnumeratorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex,
	                                            MonoObject** OutValue);
};
