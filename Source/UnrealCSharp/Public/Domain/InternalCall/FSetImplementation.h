#pragma once

#include "mono/metadata/object.h"

class FSetImplementation
{
public:
	static void RegisterSetImplementation(MonoObject InMonoObject, MonoReflectionType* InReflectionType);

	static void UnRegisterSetImplementation(MonoObject InMonoObject);

	static void Set_EmptyImplementation(MonoObject InMonoObject, int32 InExpectedNumElements);

	static int32 Set_NumImplementation(MonoObject InMonoObject);

	static void Set_AddImplementation(MonoObject InMonoObject, void* InElement);

	static int32 Set_RemoveImplementation(MonoObject InMonoObject, void* InKey);

	static bool Set_ContainsImplementation(MonoObject InMonoObject, const void* InKey);
};
