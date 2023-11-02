#pragma once

#include "Reference/TContainerReference.h"

static bool operator==(const FArrayHelperAddress& A, const FArrayHelperAddress& B)
{
	return A.Address == B.Address && A.Value == B.Value;
}

static bool operator==(const FMapHelperAddress& A, const FMapHelperAddress& B)
{
	return A.Address == B.Address && A.Value == B.Value;
}

static bool operator==(const FSetHelperAddress& A, const FSetHelperAddress& B)
{
	return A.Address == B.Address && A.Value == B.Value;
}

static uint32 GetTypeHash(const FArrayHelperAddress& InArrayHelperAddress)
{
	return GetTypeHash(InArrayHelperAddress.Address != nullptr
		                   ? InArrayHelperAddress.Address
		                   : InArrayHelperAddress.Value);
}

static uint32 GetTypeHash(const FMapHelperAddress& InMapHelperAddress)
{
	return GetTypeHash(InMapHelperAddress.Address != nullptr
		                   ? InMapHelperAddress.Address
		                   : InMapHelperAddress.Value);
}

static uint32 GetTypeHash(const FSetHelperAddress& InSetHelperAddress)
{
	return GetTypeHash(InSetHelperAddress.Address != nullptr
		                   ? InSetHelperAddress.Address
		                   : InSetHelperAddress.Value);
}

template <
	typename Class,
	typename FContainerValueMapping,
	typename FContainerValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FContainerValueMapping::FKey2GarbageCollectionHandle Class::* Key2GarbageCollectionHandle,
	typename FContainerValueMapping::FMonoObject2Value Class::* MonoObject2Value,
	typename FContainerValueMapping::FAddress2GarbageCollectionHandle Class::* Address2GarbageCollectionHandle
>
struct FContainerRegistry::TContainerRegistryImplementation<
		FContainerValueMapping,
		typename FContainerValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FContainerValueMapping::FKey2GarbageCollectionHandle Class::*,
		Key2GarbageCollectionHandle,
		typename FContainerValueMapping::FMonoObject2Value Class::*,
		MonoObject2Value,
		typename FContainerValueMapping::FAddress2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandle
	>
{
	static typename FContainerValueMapping::ValueType::Type GetContainer(
		Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr ? FoundValue->Value : nullptr;
	}

	static typename FContainerValueMapping::ValueType::Type GetContainer(
		Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundValue = (InRegistry->*MonoObject2Value).Find(InMonoObject);

		return FoundValue != nullptr ? FoundValue->Value : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const typename FContainerValueMapping::FAddressType InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, const typename FContainerValueMapping::FAddressType InAddress,
	                         typename FContainerValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(typename FContainerValueMapping::KeyType(InValue, InAddress),
		                                               GarbageCollectionHandle);

		if (InAddress != nullptr)
		{
			(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);
		}

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FContainerValueMapping::ValueType(
			                                                 InValue, InAddress));

		(InRegistry->*MonoObject2Value).Add(InMonoObject,
		                                    typename FContainerValueMapping::ValueType(InValue, InAddress));

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner,
	                         const typename FContainerValueMapping::FAddressType InAddress,
	                         typename FContainerValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(typename FContainerValueMapping::KeyType(InValue, InAddress),
		                                               GarbageCollectionHandle);

		(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FContainerValueMapping::ValueType(
			                                                 InValue, InAddress));

		(InRegistry->*MonoObject2Value).Add(InMonoObject,
		                                    typename FContainerValueMapping::ValueType(InValue, InAddress));

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TContainerReference<std::remove_pointer_t<typename FContainerValueMapping::ValueType::Type>>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Key2GarbageCollectionHandle).Remove(*FoundValue);

			if (FoundValue->Address != nullptr)
			{
				(InRegistry->*Address2GarbageCollectionHandle).Remove(FoundValue->Address);
			}

			if (FoundValue->Value != nullptr)
			{
				delete FoundValue->Value;

				FoundValue->Value = nullptr;
			}

			(InRegistry->*MonoObject2Value).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FArrayHelperValueMapping::ValueType::Type>> :
	TContainerRegistryImplementation<
		FArrayHelperValueMapping,
		decltype(&FContainerRegistry::GarbageCollectionHandle2ArrayHelperAddress),
		&FContainerRegistry::GarbageCollectionHandle2ArrayHelperAddress,
		decltype(&FContainerRegistry::ArrayHelperAddress2GarbageCollectionHandle),
		&FContainerRegistry::ArrayHelperAddress2GarbageCollectionHandle,
		decltype(&FContainerRegistry::MonoObject2ArrayHelperAddress),
		&FContainerRegistry::MonoObject2ArrayHelperAddress,
		decltype(&FContainerRegistry::ArrayAddress2GarbageCollectionHandle),
		&FContainerRegistry::ArrayAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FMapHelperValueMapping::ValueType::Type>> :
	TContainerRegistryImplementation<
		FMapHelperValueMapping,
		decltype(&FContainerRegistry::GarbageCollectionHandle2MapHelperAddress),
		&FContainerRegistry::GarbageCollectionHandle2MapHelperAddress,
		decltype(&FContainerRegistry::MapHelperAddress2GarbageCollectionHandle),
		&FContainerRegistry::MapHelperAddress2GarbageCollectionHandle,
		decltype(&FContainerRegistry::MonoObject2MapHelperAddress),
		&FContainerRegistry::MonoObject2MapHelperAddress,
		decltype(&FContainerRegistry::MapAddress2GarbageCollectionHandle),
		&FContainerRegistry::MapAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FContainerRegistry::TContainerRegistry<std::remove_pointer_t<
		FContainerRegistry::FSetHelperValueMapping::ValueType::Type>> :
	TContainerRegistryImplementation<
		FSetHelperValueMapping,
		decltype(&FContainerRegistry::GarbageCollectionHandle2SetHelperAddress),
		&FContainerRegistry::GarbageCollectionHandle2SetHelperAddress,
		decltype(&FContainerRegistry::SetHelperAddress2GarbageCollectionHandle),
		&FContainerRegistry::SetHelperAddress2GarbageCollectionHandle,
		decltype(&FContainerRegistry::MonoObject2SetHelperAddress),
		&FContainerRegistry::MonoObject2SetHelperAddress,
		decltype(&FContainerRegistry::SetAddress2GarbageCollectionHandle),
		&FContainerRegistry::SetAddress2GarbageCollectionHandle
	>
{
};
