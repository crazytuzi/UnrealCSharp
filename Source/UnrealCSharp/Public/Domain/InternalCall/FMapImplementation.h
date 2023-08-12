#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FMapImplementation
{
public:
	static void Map_RegisterImplementation(MonoObject* InMonoObject);

	static void Map_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Map_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                    int32 InExpectedNumElements);

	static int32 Map_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Map_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey,
	                                  MonoObject* InValue);

	static int32 Map_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey);

	static void Map_FindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InValue,
	                                      MonoObject** OutKey);

	static void Map_FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey,
	                                   MonoObject** OutValue);

	static bool Map_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey);

	static void Map_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey,
	                                  MonoObject** OutValue);

	static void Map_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey,
	                                  MonoObject* InValue);

	static int32 Map_GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Map_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex);

	static void Map_GetEnumeratorKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               int32 InIndex, MonoObject** OutKey);

	static void Map_GetEnumeratorValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 int32 InIndex, MonoObject** OutValue);
};
