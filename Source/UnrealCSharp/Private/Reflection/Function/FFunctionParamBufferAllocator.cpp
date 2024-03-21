#include "Reflection/Function/FFunctionParamBufferAllocator.h"

FFunctionParamBufferAllocator::FFunctionParamBufferAllocator(const UFunction& Func)
	: Counter(0)
{
	ParmsSize = Func.ParmsSize;
}

FFunctionParamBufferAllocator::~FFunctionParamBufferAllocator()
{
	for (int i = 0; i < Buffers.Num(); ++i)
	{
		FMemory::Free(Buffers[i]);
	}
}

void* FFunctionParamBufferAllocator::Get()
{
	if (Counter < Buffers.Num())
	{
		return Buffers[Counter++];
	}
	Counter++;
	const auto Buffer = FMemory::Malloc(ParmsSize, 16);
	FMemory::Memzero(Buffer, ParmsSize);
	Buffers.Add(Buffer);
	return Buffer;
}


void FFunctionParamBufferAllocator::Pop(void* Memory)
{
	check(Counter > 0);
	Counter--;
	check(Buffers[Counter] == Memory);
}
