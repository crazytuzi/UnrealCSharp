#pragma once

#include "mono/metadata/object.h"

class FArrayImplementation
{
public:
	static void RegisterArrayImplementation(MonoObject InMonoObject, MonoReflectionType* InReflectionType);

	static void UnRegisterArrayImplementation(MonoObject InMonoObject);

	static int32 Array_GetTypeSizeImplementation(MonoObject InMonoObject);

	static int32 Array_GetSlackImplementation(MonoObject InMonoObject);

	static bool Array_IsValidIndexImplementation(MonoObject InMonoObject, int32 InIndex);

	static int32 Array_NumImplementation(MonoObject InMonoObject);

	static int32 Array_MaxImplementation(MonoObject InMonoObject);

	static void Array_GetImplementation(MonoObject InMonoObject, int32 InIndex, MonoObject** OutValue);

	static void Array_SetImplementation(MonoObject InMonoObject, int32 InIndex, void* InValue);

	static int32 Array_FindImplementation(MonoObject InMonoObject, void* InValue);

	static int32 Array_FindLastImplementation(MonoObject InMonoObject, void* InValue);

	static bool Array_ContainsImplementation(MonoObject InMonoObject, void* InValue);

	static int32 Array_AddUninitializedImplementation(MonoObject InMonoObject, int32 InCount);

	static void Array_InsertZeroedImplementation(MonoObject InMonoObject, int32 InIndex, int32 InCount);

	static void Array_InsertDefaultedImplementation(MonoObject InMonoObject, int32 InIndex, int32 InCount);

	static void Array_RemoveAtImplementation(MonoObject InMonoObject, int32 InIndex, int32 InCount,
	                                         bool bAllowShrinking);

	static void Array_ResetImplementation(MonoObject InMonoObject, int32 InNewSize);

	static void Array_EmptyImplementation(MonoObject InMonoObject, int32 InSlack);

	static void Array_SetNumImplementation(MonoObject InMonoObject, int32 InNewNum, bool bAllowShrinking);

	static int32 Array_AddImplementation(MonoObject InMonoObject, void* InValue);

	static int32 Array_AddZeroedImplementation(MonoObject InMonoObject, int32 InCount);

	static int32 Array_AddUniqueImplementation(MonoObject InMonoObject, void* InValue);

	static int32 Array_RemoveSingleImplementation(MonoObject InMonoObject, const void* InValue);

	static int32 Array_RemoveImplementation(MonoObject InMonoObject, const void* InValue);

	static void Array_SwapMemoryImplementation(MonoObject InMonoObject, int32 InFirstIndexToSwap,
	                                           int32 InSecondIndexToSwap);

	static void Array_SwapImplementation(MonoObject InMonoObject, int32 InFirstIndexToSwap, int32 InSecondIndexToSwap);
};
