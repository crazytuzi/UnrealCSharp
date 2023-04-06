#pragma once

#include "mono/metadata/object-forward.h"

class FSetImplementation
{
public:
	static void Set_RegisterImplementation(MonoObject* InMonoObject);

	static void Set_UnRegisterImplementation(const MonoObject* InMonoObject);

	static void Set_EmptyImplementation(const MonoObject* InMonoObject, int32 InExpectedNumElements);

	static int32 Set_NumImplementation(const MonoObject* InMonoObject);

	static void Set_AddImplementation(const MonoObject* InMonoObject, void* InElement);

	static int32 Set_RemoveImplementation(const MonoObject* InMonoObject, void* InKey);

	static bool Set_ContainsImplementation(const MonoObject* InMonoObject, const void* InKey);

	static TArray<FProperty*> Set_ToArrayImplementation(const MonoObject* InMonoObject);

	static void  Set_FindImplementation(const MonoObject* InMonoObject,int32 Index,void* Value);
	
	static int32 Set_GetMaxIndexImplementation(const MonoObject* InMonoObject);
	
	static TSet<void*> Set_UnionImplementation(const MonoObject* InMonoObject,TSet<void*> OtherSet);

};
