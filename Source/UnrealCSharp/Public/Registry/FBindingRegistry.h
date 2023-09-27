#pragma once

#include "TValueMapping.inl"

struct FBindingAddressWrapper
{
	virtual ~FBindingAddressWrapper()
	{
	}

	virtual void* GetValue()
	{
		return nullptr;
	}
};

template <typename T>
struct TBindingAddressWrapper : FBindingAddressWrapper
{
	explicit TBindingAddressWrapper(T* InValue): Value(InValue)
	{
	}

	virtual ~TBindingAddressWrapper() override
	{
		delete Value;
	}

	virtual void* GetValue() override
	{
		return (void*)Value;
	}

private:
	T* Value;
};

struct FBindingAddress
{
	FBindingAddressWrapper* AddressWrapper;

	bool bNeedFree;

	FBindingAddress(FBindingAddressWrapper* InAddressWrapper, const bool InNeedFree = true):
		AddressWrapper(InAddressWrapper),
		bNeedFree(InNeedFree)
	{
	}
};

static bool operator==(const FBindingAddress& A, const FBindingAddress& B);

static uint32 GetTypeHash(const FBindingAddress& InBindingAddress);

class UNREALCSHARP_API FBindingRegistry
{
public:
	FBindingRegistry();

	~FBindingRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	template <typename T>
	auto GetBinding(const MonoObject* InMonoObject);

	MonoObject* GetObject(const void* InObject);

public:
	template <typename T>
	auto AddReference(const T* InObject, MonoObject* InMonoObject, bool bNeedFree = true);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TValueMapping<void*, FBindingAddress>::GarbageCollectionHandle2Value GarbageCollectionHandle2BindingAddress;

	TValueMapping<void*, FBindingAddress>::Value2GarbageCollectionHandle BindingAddress2GarbageCollectionHandle;

	TValueMapping<void*, FBindingAddress>::MonoObject2Value MonoObject2BindingAddress;
};

#include "FBindingRegistry.inl"
