#pragma once

class FFunctionParamBufferAllocator
{
public:
	FFunctionParamBufferAllocator();

	virtual ~FFunctionParamBufferAllocator();

	virtual void* Malloc();

	virtual void Free(void* InMemory);
};

class FFunctionParamEmptyBufferAllocator final : public FFunctionParamBufferAllocator
{
public:
	using FFunctionParamBufferAllocator::FFunctionParamBufferAllocator;
};

class FFunctionParamPoolBufferAllocator final : public FFunctionParamBufferAllocator
{
public:
	explicit FFunctionParamPoolBufferAllocator(const TWeakObjectPtr<UFunction>& InFunction);

	virtual ~FFunctionParamPoolBufferAllocator() override;

public:
	virtual void* Malloc() override;

	virtual void Free(void* InMemory) override;

private:
	uint8 Count;

	decltype(UFunction::ParmsSize) ParamSize;

	TArray<void*> Buffers;
};

class FFunctionParamPersistentBufferAllocator final : public FFunctionParamBufferAllocator
{
public:
	explicit FFunctionParamPersistentBufferAllocator(const TWeakObjectPtr<UFunction>& InFunction);

	virtual ~FFunctionParamPersistentBufferAllocator() override;

public:
	virtual void* Malloc() override;

	virtual void Free(void* InMemory) override;

private:
	void* Params;
};

class FFunctionParamBufferAllocatorFactory
{
public:
	template <typename BufferAllocatorType, typename EmptyBufferAllocatorType = FFunctionParamEmptyBufferAllocator>
	static TSharedRef<FFunctionParamBufferAllocator> Factory(const TWeakObjectPtr<UFunction>& InFunction)
	{
		if (InFunction->ParmsSize > 0)
		{
			return MakeShared<BufferAllocatorType>(InFunction);
		}

		static EmptyBufferAllocatorType EmptyBufferAllocator;

		return MakeShared<EmptyBufferAllocatorType>(EmptyBufferAllocator);
	}
};
