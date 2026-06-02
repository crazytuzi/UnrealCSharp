#pragma once

#include "Reference/TDelegateReference.h"

template <
	typename Class,
	typename FDelegateValueMapping,
	typename FDelegateValueMapping::FManagedHandle2Value Class::* ManagedHandle2Value,
	typename FDelegateValueMapping::FAddress2ManagedHandle Class::* Address2ManagedHandle
>
struct FDelegateRegistry::TDelegateRegistryImplementation<
		FDelegateValueMapping,
		typename FDelegateValueMapping::FManagedHandle2Value Class::*,
		ManagedHandle2Value,
		typename FDelegateValueMapping::FAddress2ManagedHandle Class::*,
		Address2ManagedHandle
	>
{
	static auto GetDelegate(Class* InRegistry, const IManagedHandle InManagedHandle)
		-> typename FDelegateValueMapping::ValueType
	{
		const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle);

		return FoundValue != nullptr ? *FoundValue : nullptr;
	}

	static auto GetObject(Class* InRegistry, const typename FDelegateValueMapping::FAddressType InAddress)
		-> IManagedHandle
	{
		const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(InAddress);

		return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
	}

	static auto AddReference(Class* InRegistry, typename FDelegateValueMapping::ValueType InValue,
	                         const FClassReflection* InClass, const IManagedHandle InManagedHandle)
	{
		const auto ManagedHandle = InClass->NewWeakRefGCHandle(InManagedHandle, true);

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle, InValue);

		return true;
	}

	static auto AddReference(Class* InRegistry, const IManagedHandle InOwner,
	                         const typename FDelegateValueMapping::FAddressType InAddress,
	                         typename FDelegateValueMapping::ValueType InValue,
	                         const FClassReflection* InClass, const IManagedHandle InManagedHandle)
	{
		const auto ManagedHandle = InClass->NewGCHandle(InManagedHandle, true);

		(InRegistry->*Address2ManagedHandle).Add(InAddress, ManagedHandle);

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle, InValue);

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TDelegateReference<std::remove_pointer_t<typename FDelegateValueMapping::ValueType>>(ManagedHandle));
	}

	static auto RemoveReference(Class* InRegistry, const IManagedHandle InManagedHandle)
	{
		if (const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle))
		{
			const auto Address = (*FoundValue)->GetAddress();

			if (const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(Address))
			{
				if (*FoundManagedHandle == InManagedHandle)
				{
					(InRegistry->*Address2ManagedHandle).Remove(Address);
				}
			}

			delete *FoundValue;

			(InRegistry->*ManagedHandle2Value).Remove(InManagedHandle);

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
		decltype(&FDelegateRegistry::DelegateManagedHandle2Helper),
		&FDelegateRegistry::DelegateManagedHandle2Helper,
		decltype(&FDelegateRegistry::DelegateAddress2ManagedHandle),
		&FDelegateRegistry::DelegateAddress2ManagedHandle
	>
{
};

template <>
struct FDelegateRegistry::TDelegateRegistry<std::remove_pointer_t<
		FDelegateRegistry::FMulticastDelegateHelperMapping::ValueType>> :
	TDelegateRegistryImplementation<
		FMulticastDelegateHelperMapping,
		decltype(&FDelegateRegistry::MulticastDelegateManagedHandle2Helper),
		&FDelegateRegistry::MulticastDelegateManagedHandle2Helper,
		decltype(&FDelegateRegistry::MulticastDelegateAddress2ManagedHandle),
		&FDelegateRegistry::MulticastDelegateAddress2ManagedHandle
	>
{
};
