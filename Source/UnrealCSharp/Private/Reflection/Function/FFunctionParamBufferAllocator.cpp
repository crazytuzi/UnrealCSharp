#include "Reflection/Function/FFunctionParamBufferAllocator.h"

FFunctionParamBufferAllocator::FFunctionParamBufferAllocator()
{
}

FFunctionParamBufferAllocator::~FFunctionParamBufferAllocator()
{
}

void* FFunctionParamBufferAllocator::Malloc()
{
	return nullptr;
}

void FFunctionParamBufferAllocator::Free(void* InMemory)
{
}

FFunctionParamPoolBufferAllocator::FFunctionParamPoolBufferAllocator(
	const TWeakObjectPtr<UFunction>& InFunction):
	Count(0),
	ParamSize(InFunction->ParmsSize)
{
}

FFunctionParamPoolBufferAllocator::~FFunctionParamPoolBufferAllocator()
{
	for (const auto Buffer : Buffers)
	{
		FMemory::Free(Buffer);
	}
}

void* FFunctionParamPoolBufferAllocator::Malloc()
{
	if (Buffers.IsValidIndex(Count))
	{
		return Buffers[Count++];
	}

	Count++;

	const auto Buffer = FMemory::Malloc(ParamSize, 16);

	FMemory::Memzero(Buffer, ParamSize);

	Buffers.Add(Buffer);

	return Buffer;
}

void FFunctionParamPoolBufferAllocator::Free(void* InMemory)
{
	Count--;
}

FFunctionParamPersistentBufferAllocator::FFunctionParamPersistentBufferAllocator(
	const TWeakObjectPtr<UFunction>& InFunction)
{
	Params = FMemory::Malloc(InFunction->ParmsSize, 16);

	FMemory::Memzero(Params, InFunction->ParmsSize);
}

FFunctionParamPersistentBufferAllocator::~FFunctionParamPersistentBufferAllocator()
{
	if (Params != nullptr)
	{
		FMemory::Free(Params);

		Params = nullptr;
	}
}

void* FFunctionParamPersistentBufferAllocator::Malloc()
{
	return Params;
}

void FFunctionParamPersistentBufferAllocator::Free(void* InMemory)
{
}
