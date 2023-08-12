#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FArrayImplementation
{
public:
	static void Array_RegisterImplementation(MonoObject* InMonoObject);

	static void Array_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Array_GetTypeSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Array_GetSlackImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Array_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             int32 InIndex);

	static int32 Array_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Array_MaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Array_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex,
	                                    MonoObject** OutValue);

	static void Array_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex,
	                                    MonoObject* InValue);

	static int32 Array_FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      MonoObject* InValue);

	static int32 Array_FindLastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject* InValue);

	static bool Array_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject* InValue);

	static int32 Array_AddUninitializedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  int32 InCount);

	static void Array_InsertZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             int32 InIndex, int32 InCount);

	static void Array_InsertDefaultedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                int32 InIndex, int32 InCount);

	static void Array_RemoveAtImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InIndex,
	                                         int32 InCount, bool bAllowShrinking);

	static void Array_ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InNewSize);

	static void Array_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InSlack);

	static void Array_SetNumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InNewNum,
	                                       bool bAllowShrinking);

	static int32 Array_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InValue);

	static int32 Array_AddZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 InCount);

	static int32 Array_AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject* InValue);

	static int32 Array_RemoveSingleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject* InValue);

	static int32 Array_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject* InValue);

	static void Array_SwapMemoryImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           int32 InFirstIndexToSwap, int32 InSecondIndexToSwap);

	static void Array_SwapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                     int32 InFirstIndexToSwap, int32 InSecondIndexToSwap);
};
