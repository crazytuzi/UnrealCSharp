#pragma once

#include "mono/metadata/object.h"

class FMapImplementation
{
public:
	static void Map_RegisterImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                                       MonoReflectionType* InValueReflectionType);

	static void Map_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void Map_EmptyImplementation(const MonoObject* InMonoObject, int32 InExpectedNumElements);

	static int32 Map_NumImplementation(const MonoObject* InMonoObject);

	static void Map_AddImplementation(const MonoObject* InMonoObject, void* InKey, void* InValue);

	static int32 Map_RemoveImplementation(const MonoObject* InMonoObject, void* InKey);

	static void Map_FindKeyImplementation(const MonoObject* InMonoObject, void* InValue, MonoObject** OutKey);

	static void Map_FindImplementation(const MonoObject* InMonoObject, void* InKey, MonoObject** OutValue);

	static bool Map_ContainsImplementation(const MonoObject* InMonoObject, const void* InKey);

	static void Map_GetImplementation(const MonoObject* InMonoObject, void* InKey, MonoObject** OutValue);

	static void Map_SetImplementation(const MonoObject* InMonoObject, void* InKey, void* InValue);
};
