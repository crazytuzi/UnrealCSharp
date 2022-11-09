#pragma once

#include "mono/metadata/object.h"

class FMapImplementation
{
public:
	static void RegisterMapImplementation(MonoObject InMonoObject, MonoReflectionType* InKeyReflectionType,
	                                      MonoReflectionType* InValueReflectionType);

	static void UnRegisterMapImplementation(MonoObject InMonoObject);

	static void Map_EmptyImplementation(MonoObject InMonoObject, int32 InExpectedNumElements);

	static int32 Map_NumImplementation(MonoObject InMonoObject);

	static void Map_AddImplementation(MonoObject InMonoObject, void* InKey, void* InValue);

	static int32 Map_RemoveImplementation(MonoObject InMonoObject, void* InKey);

	static void Map_FindKeyImplementation(MonoObject InMonoObject, void* InValue, MonoObject** OutKey);

	static void Map_FindImplementation(MonoObject InMonoObject, void* InKey, MonoObject** OutValue);

	static bool Map_ContainsImplementation(MonoObject InMonoObject, const void* InKey);

	static void Map_GetImplementation(MonoObject InMonoObject, void* InKey, MonoObject** OutValue);

	static void Map_SetImplementation(MonoObject InMonoObject, void* InKey, void* InValue);
};
