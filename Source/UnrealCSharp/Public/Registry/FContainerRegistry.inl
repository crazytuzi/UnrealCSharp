#pragma once

#include "Reference/TContainerReference.h"

template <
	typename Class,
	typename FContainerValueMapping,
	typename FContainerValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FContainerValueMapping::FMonoObject2Value Class::* MonoObject2Value,
	typename FContainerValueMapping::FAddress2GarbageCollectionHandle Class::* Address2GarbageCollectionHandle
>
struct FContainerRegistry::TContainerRegistryImplementation<
		FContainerValueMapping,
		typename FContainerValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FContainerValueMapping::FMonoObject2Value Class::*,
		MonoObject2Value,
		typename FContainerValueMapping::FAddress2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandle
	>
{
	static typename FContainerValueMapping::ValueType GetContainer(
		Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr ? *FoundValue : nullptr;
	}

	static typename FContainerValueMapping::ValueType GetContainer(
		Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundValue = (InRegistry->*MonoObject2Value).Find(InMonoObject);

		return FoundValue != nullptr ? *FoundValue : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const typename FContainerValueMapping::FAddressType InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, typename FContainerValueMapping::ValueType InValue,
	                         MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle, InValue);

		(InRegistry->*MonoObject2Value).Add(InMonoObject, InValue);

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner,
	                         const typename FContainerValueMapping::FAddressType InAddress,
	                         typename FContainerValueMapping::ValueType InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle, InValue);

		(InRegistry->*MonoObject2Value).Add(InMonoObject, InValue);

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TContainerReference<std::remove_pointer_t<typename FContainerValueMapping::ValueType>>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			if (const auto FoundAddress = (InRegistry->*Address2GarbageCollectionHandle).FindKey(
				InGarbageCollectionHandle))
			{
				(InRegistry->*Address2GarbageCollectionHandle).Remove(*FoundAddress);
			}

			delete *FoundValue;

			(InRegistry->*MonoObject2Value).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

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
		decltype(&FContainerRegistry::ArrayGarbageCollectionHandle2Helper),
		&FContainerRegistry::ArrayGarbageCollectionHandle2Helper,
		decltype(&FContainerRegistry::ArrayMonoObject2Helper),
		&FContainerRegistry::ArrayMonoObject2Helper,
		decltype(&FContainerRegistry::ArrayAddress2GarbageCollectionHandle),
		&FContainerRegistry::ArrayAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FMapHelperValueMapping::ValueType>> :
	TContainerRegistryImplementation<
		FMapHelperValueMapping,
		decltype(&FContainerRegistry::MapGarbageCollectionHandle2Helper),
		&FContainerRegistry::MapGarbageCollectionHandle2Helper,
		decltype(&FContainerRegistry::MapMonoObject2Helper),
		&FContainerRegistry::MapMonoObject2Helper,
		decltype(&FContainerRegistry::MapAddress2GarbageCollectionHandle),
		&FContainerRegistry::MapAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FSetHelperValueMapping::ValueType>> :
	TContainerRegistryImplementation<
		FSetHelperValueMapping,
		decltype(&FContainerRegistry::SetGarbageCollectionHandle2Helper),
		&FContainerRegistry::SetGarbageCollectionHandle2Helper,
		decltype(&FContainerRegistry::SetMonoObject2Helper),
		&FContainerRegistry::SetMonoObject2Helper,
		decltype(&FContainerRegistry::SetAddress2GarbageCollectionHandle),
		&FContainerRegistry::SetAddress2GarbageCollectionHandle
	>
{
};
