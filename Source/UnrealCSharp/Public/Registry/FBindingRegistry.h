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
struct TBindingAddressWrapper final : FBindingAddressWrapper
{
	explicit TBindingAddressWrapper(T* InValue):
		Value(InValue)
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
	typedef FBindingAddressWrapper FWrapperType;

	FWrapperType* AddressWrapper;

	bool bNeedFree;

	explicit FBindingAddress(FWrapperType* InAddressWrapper, const bool InNeedFree = true):
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
	template <typename Key, typename Value>
	struct TBindingValueMapping : TValueMapping<Key, Value>
	{
	};

	typedef TBindingValueMapping<void*, FBindingAddress> FBindingValueMapping;

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

	MonoObject* GetObject(const FBindingValueMapping::KeyType InObject);

public:
	template <typename T>
	auto AddReference(const T* InObject, MonoObject* InMonoObject);

	template <typename T>
	auto AddReference(const FGarbageCollectionHandle& InOwner, const T* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FBindingValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2BindingAddress;

	FBindingValueMapping::FKey2GarbageCollectionHandle BindingAddress2GarbageCollectionHandle;

	FBindingValueMapping::FMonoObject2Value MonoObject2BindingAddress;
};

#include "FBindingRegistry.inl"
