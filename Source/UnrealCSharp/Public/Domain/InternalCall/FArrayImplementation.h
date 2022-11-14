#pragma once

#include "mono/metadata/object.h"

class FArrayImplementation
{
public:
	static void Array_RegisterImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static void Array_UnRegisterImplementation(const MonoObject* InMonoObject);

	static int32 Array_GetTypeSizeImplementation(const MonoObject* InMonoObject);

	static int32 Array_GetSlackImplementation(const MonoObject* InMonoObject);

	static bool Array_IsValidIndexImplementation(const MonoObject* InMonoObject, int32 InIndex);

	static int32 Array_NumImplementation(const MonoObject* InMonoObject);

	static int32 Array_MaxImplementation(const MonoObject* InMonoObject);

	static void Array_GetImplementation(const MonoObject* InMonoObject, int32 InIndex, MonoObject** OutValue);

	static void Array_SetImplementation(const MonoObject* InMonoObject, int32 InIndex, void* InValue);

	static int32 Array_FindImplementation(const MonoObject* InMonoObject, void* InValue);

	static int32 Array_FindLastImplementation(const MonoObject* InMonoObject, void* InValue);

	static bool Array_ContainsImplementation(const MonoObject* InMonoObject, void* InValue);

	static int32 Array_AddUninitializedImplementation(const MonoObject* InMonoObject, int32 InCount);

	static void Array_InsertZeroedImplementation(const MonoObject* InMonoObject, int32 InIndex, int32 InCount);

	static void Array_InsertDefaultedImplementation(const MonoObject* InMonoObject, int32 InIndex, int32 InCount);

	static void Array_RemoveAtImplementation(const MonoObject* InMonoObject, int32 InIndex, int32 InCount,
	                                         bool bAllowShrinking);

	static void Array_ResetImplementation(const MonoObject* InMonoObject, int32 InNewSize);

	static void Array_EmptyImplementation(const MonoObject* InMonoObject, int32 InSlack);

	static void Array_SetNumImplementation(const MonoObject* InMonoObject, int32 InNewNum, bool bAllowShrinking);

	static int32 Array_AddImplementation(const MonoObject* InMonoObject, void* InValue);

	static int32 Array_AddZeroedImplementation(const MonoObject* InMonoObject, int32 InCount);

	static int32 Array_AddUniqueImplementation(const MonoObject* InMonoObject, void* InValue);

	static int32 Array_RemoveSingleImplementation(const MonoObject* InMonoObject, const void* InValue);

	static int32 Array_RemoveImplementation(const MonoObject* InMonoObject, const void* InValue);

	static void Array_SwapMemoryImplementation(const MonoObject* InMonoObject, int32 InFirstIndexToSwap,
	                                           int32 InSecondIndexToSwap);

	static void Array_SwapImplementation(const MonoObject* InMonoObject, int32 InFirstIndexToSwap,
	                                     int32 InSecondIndexToSwap);
};
