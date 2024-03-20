#pragma once

#include "Stats/Stats.h"

DECLARE_STATS_GROUP(TEXT("UnrealCSharp"), STATGROUP_UnrealCSharp, STATCAT_Advanced);

DECLARE_MEMORY_STAT_EXTERN(TEXT("Function Param Buffer Memory"), STAT_UnrealCSharp_FunctionParamBuffer_Memory, STATGROUP_UnrealCSharp, UNREALCSHARP_API);

DECLARE_MEMORY_STAT_EXTERN(TEXT("Total Function Param Buffer Memory"), STAT_UnrealCSharp_TotalFunctionParamBuffer_Memory, STATGROUP_UnrealCSharp, UNREALCSHARP_API);

DEFINE_STAT(STAT_UnrealCSharp_FunctionParamBuffer_Memory);

DEFINE_STAT(STAT_UnrealCSharp_TotalFunctionParamBuffer_Memory);

class FFunctionParamBufferAllocator
{
public:
	explicit FFunctionParamBufferAllocator(const UFunction& Func);

	virtual ~FFunctionParamBufferAllocator() ;

	virtual void* Get() ;

	virtual void Pop(void* Memory) ;

private:
	uint8 Counter;
	
	uint16 ParmsSize;
	
	TArray<void*> Buffers;
};
