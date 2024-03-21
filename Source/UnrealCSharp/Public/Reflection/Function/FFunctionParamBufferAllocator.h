#pragma once

class FFunctionParamBufferAllocator
{
public:
	explicit FFunctionParamBufferAllocator(const UFunction& Func);

	~FFunctionParamBufferAllocator();

	void* Get();

	void Pop(void* Memory);

private:
	uint8 Counter;

	uint16 ParmsSize;

	TArray<void*> Buffers;
};
