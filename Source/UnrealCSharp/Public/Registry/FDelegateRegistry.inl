#pragma once

#include "Reference/TDelegateReference.h"

template <
	typename Class,
	typename FDelegateValueMapping,
	typename FDelegateValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FDelegateValueMapping::FAddress2GarbageCollectionHandle Class::* Address2GarbageCollectionHandle
>
struct FDelegateRegistry::TDelegateRegistryImplementation<
		FDelegateValueMapping,
		typename FDelegateValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FDelegateValueMapping::FAddress2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandle
	>
{
	static typename FDelegateValueMapping::ValueType GetDelegate(Class* InRegistry,
	                                                             const FGarbageCollectionHandle&
	                                                             InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr ? *FoundValue : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const typename FDelegateValueMapping::FAddressType InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, typename FDelegateValueMapping::ValueType InValue,
	                         MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle, InValue);

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner,
	                         const typename FDelegateValueMapping::FAddressType InAddress,
	                         typename FDelegateValueMapping::ValueType InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle, InValue);

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TDelegateReference<std::remove_pointer_t<typename FDelegateValueMapping::ValueType>>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Address2GarbageCollectionHandle).Remove(*FoundValue);

			delete *FoundValue;

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FDelegateRegistry::TDelegateRegistry<std::remove_pointer_t<
		FDelegateRegistry::FDelegateHelperMapping::ValueType>> :
	TDelegateRegistryImplementation<
		FDelegateHelperMapping,
		decltype(&FDelegateRegistry::DelegateGarbageCollectionHandle2Helper),
		&FDelegateRegistry::DelegateGarbageCollectionHandle2Helper,
		decltype(&FDelegateRegistry::DelegateAddress2GarbageCollectionHandle),
		&FDelegateRegistry::DelegateAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FDelegateRegistry::TDelegateRegistry<std::remove_pointer_t<
		FDelegateRegistry::FMulticastDelegateHelperMapping::ValueType>> :
	TDelegateRegistryImplementation<
		FMulticastDelegateHelperMapping,
		decltype(&FDelegateRegistry::MulticastDelegateGarbageCollectionHandle2Helper),
		&FDelegateRegistry::MulticastDelegateGarbageCollectionHandle2Helper,
		decltype(&FDelegateRegistry::MulticastDelegateAddress2GarbageCollectionHandle),
		&FDelegateRegistry::MulticastDelegateAddress2GarbageCollectionHandle
	>
{
};
