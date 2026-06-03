#pragma once

#include "Reference/TContainerReference.h"

template <
	typename Class,
	typename FContainerValueMapping,
	typename FContainerValueMapping::FManagedHandle2Value Class::* ManagedHandle2Value,
	typename FContainerValueMapping::FAddress2ManagedHandle Class::* Address2ManagedHandle
>
struct FContainerRegistry::TContainerRegistryImplementation<
		FContainerValueMapping,
		typename FContainerValueMapping::FManagedHandle2Value Class::*,
		ManagedHandle2Value,
		typename FContainerValueMapping::FAddress2ManagedHandle Class::*,
		Address2ManagedHandle
	>
{
	static auto GetContainer(Class* InRegistry, const IManagedHandle InManagedHandle)
		-> typename FContainerValueMapping::ValueType
	{
		const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle);

		return FoundValue != nullptr ? *FoundValue : nullptr;
	}

	static auto GetObject(Class* InRegistry, const typename FContainerValueMapping::FAddressType InAddress)
		-> IManagedHandle
	{
		const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(InAddress);

		return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
	}

	static auto AddReference(Class* InRegistry, typename FContainerValueMapping::ValueType InValue,
	                         const FClassReflection* InClass, const IManagedHandle InManagedHandle)
	{
		const auto ManagedHandle = InClass->NewWeakRefGCHandle(InManagedHandle, true);

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle, InValue);

		return true;
	}

	static auto AddReference(Class* InRegistry, const IManagedHandle InOwner,
	                         const typename FContainerValueMapping::FAddressType InAddress,
	                         typename FContainerValueMapping::ValueType InValue,
	                         const FClassReflection* InClass, const IManagedHandle InManagedHandle)
	{
		const auto ManagedHandle = InClass->NewGCHandle(InManagedHandle, true);

		(InRegistry->*Address2ManagedHandle).Add(InAddress, ManagedHandle);

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle, InValue);

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TContainerReference<std::remove_pointer_t<typename FContainerValueMapping::ValueType>>(ManagedHandle));
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
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FArrayHelperValueMapping::ValueType>> :
	TContainerRegistryImplementation<
		FArrayHelperValueMapping,
		decltype(&FContainerRegistry::ArrayManagedHandle2Helper),
		&FContainerRegistry::ArrayManagedHandle2Helper,
		decltype(&FContainerRegistry::ArrayAddress2ManagedHandle),
		&FContainerRegistry::ArrayAddress2ManagedHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FMapHelperValueMapping::ValueType>> :
	TContainerRegistryImplementation<
		FMapHelperValueMapping,
		decltype(&FContainerRegistry::MapManagedHandle2Helper),
		&FContainerRegistry::MapManagedHandle2Helper,
		decltype(&FContainerRegistry::MapAddress2ManagedHandle),
		&FContainerRegistry::MapAddress2ManagedHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FSetHelperValueMapping::ValueType>> :
	TContainerRegistryImplementation<
		FSetHelperValueMapping,
		decltype(&FContainerRegistry::SetManagedHandle2Helper),
		&FContainerRegistry::SetManagedHandle2Helper,
		decltype(&FContainerRegistry::SetAddress2ManagedHandle),
		&FContainerRegistry::SetAddress2ManagedHandle
	>
{
};
