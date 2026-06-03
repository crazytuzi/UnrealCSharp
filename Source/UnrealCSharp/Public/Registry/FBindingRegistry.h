#pragma once

#include "TValueMapping.inl"
#include "Reflection/FClassReflection.h"
#include "Domain/Script/IManagedHandle.h"

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

		typedef typename TBindingValueMapping::FKey2ManagedHandle FAddress2ManagedHandle;
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
	auto GetBinding(const IManagedHandle InManagedHandle);

	IManagedHandle GetObject(const FBindingValueMapping::FAddressType InAddress);

public:
	template <typename T, auto IsNeedFree>
	auto AddReference(const T* InObject, FClassReflection* InClass, const IManagedHandle InManagedHandle);

	template <typename T>
	auto AddReference(const IManagedHandle InOwner, const T* InObject,
	                  FClassReflection* InClass, const IManagedHandle InManagedHandle);

	bool RemoveReference(const IManagedHandle InManagedHandle);

private:
	FBindingValueMapping::FManagedHandle2Value ManagedHandle2BindingAddress;

	FBindingValueMapping::FAddress2ManagedHandle BindingAddress2ManagedHandle;
};

#include "FBindingRegistry.inl"
