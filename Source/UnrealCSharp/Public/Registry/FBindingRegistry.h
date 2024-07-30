#pragma once

#include "TValueMapping.inl"

class UNREALCSHARP_API FBindingRegistry
{
private:
	struct FBindingAddressWrapper
	{
		explicit FBindingAddressWrapper(void* InValue):
			Value(InValue)
		{
		}

		virtual ~FBindingAddressWrapper()
		{
		}

		void* Value;
	};

	template <typename T>
	struct TBindingAddressWrapper final : FBindingAddressWrapper
	{
		explicit TBindingAddressWrapper(T* InValue):
			FBindingAddressWrapper((decltype(Value))InValue)
		{
		}

		virtual ~TBindingAddressWrapper() override
		{
			delete static_cast<T*>(Value);
		}
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

	MonoObject* GetObject(const FBindingValueMapping::FAddressType InAddress);

public:
	template <typename T, auto IsNeedFree>
	auto AddReference(const T* InObject, MonoObject* InMonoObject);

	template <typename T>
	auto AddReference(const FGarbageCollectionHandle& InOwner, const T* InObject, MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FBindingValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2BindingAddress;

	FBindingValueMapping::FAddress2GarbageCollectionHandle BindingAddress2GarbageCollectionHandle;
};

#include "FBindingRegistry.inl"
