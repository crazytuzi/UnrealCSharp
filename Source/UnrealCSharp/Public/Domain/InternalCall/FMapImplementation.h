#pragma once

#include "mono/metadata/object-forward.h"

class FMapImplementation
{
public:
	static void Map_RegisterImplementation(MonoObject* InMonoObject);

	static void Map_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void Map_EmptyImplementation(const MonoObject* InMonoObject, int32 InExpectedNumElements);

	static int32 Map_NumImplementation(const MonoObject* InMonoObject);

	static void Map_AddImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject* InValue);

	static int32 Map_RemoveImplementation(const MonoObject* InMonoObject, MonoObject* InKey);

	static void Map_FindKeyImplementation(const MonoObject* InMonoObject, MonoObject* InValue, MonoObject** OutKey);

	static void Map_FindImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject** OutValue);

	static bool Map_ContainsImplementation(const MonoObject* InMonoObject, MonoObject* InKey);

	static void Map_GetImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject** OutValue);

	static void Map_SetImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject* InValue);

	static int32 Map_GetMaxIndexImplementation(const MonoObject* InMonoObject);

	static bool Map_IsValidIndexImplementation(const MonoObject* InMonoObject, int32 InIndex);

	static void Map_GetEnumeratorKeyImplementation(const MonoObject* InMonoObject, int32 InIndex, MonoObject** OutKey);

	static void Map_GetEnumeratorValueImplementation(const MonoObject* InMonoObject, int32 InIndex,
	                                                 MonoObject** OutValue);
};
