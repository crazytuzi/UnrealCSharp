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

	explicit FBindingAddress(FWrapperType* InAddressWrapper, const bool InNeedFree = true):
		AddressWrapper(InAddressWrapper),
		bNeedFree(InNeedFree)
	{
	}

	FWrapperType* AddressWrapper;

	bool bNeedFree;
};

class UNREALCSHARP_API FBindingRegistry
{
public:
	template <typename Address, typename Value>
	struct TBindingValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TBindingValueMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
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

	MonoObject* GetObject(const FBindingValueMapping::FAddressType InAddress);

public:
	template <typename T>
	auto AddReference(const T* InObject, MonoObject* InMonoObject, bool bNeedFree = true);

	template <typename T>
	auto AddReference(const FGarbageCollectionHandle& InOwner, const T* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FBindingValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2BindingAddress;

	FBindingValueMapping::FMonoObject2Value MonoObject2BindingAddress;

	FBindingValueMapping::FAddress2GarbageCollectionHandle BindingAddress2GarbageCollectionHandle;
};

#include "FBindingRegistry.inl"
