#pragma once

#include "Reference/TDelegateReference.h"

template <
	typename Class,
	typename FDelegateValueMapping,
	typename FDelegateValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FDelegateValueMapping::FKey2GarbageCollectionHandle Class::* Key2GarbageCollectionHandle
>
struct FDelegateRegistry::TDelegateRegistryImplementation<
		FDelegateValueMapping,
		typename FDelegateValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FDelegateValueMapping::FKey2GarbageCollectionHandle Class::*,
		Key2GarbageCollectionHandle
	>
{
	static typename FDelegateValueMapping::ValueType::Type GetDelegate(Class* InRegistry,
	                                                                   const FGarbageCollectionHandle&
	                                                                   InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr ? FoundValue->Value : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const typename FDelegateValueMapping::KeyType InKey)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Key2GarbageCollectionHandle).Find(InKey);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, const typename FDelegateValueMapping::KeyType InKey,
	                         typename FDelegateValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(InKey, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FDelegateValueMapping::ValueType(InValue, InKey));

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner,
	                         const typename FDelegateValueMapping::KeyType InKey,
	                         typename FDelegateValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(InKey, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FDelegateValueMapping::ValueType(InValue, InKey));

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TDelegateReference<std::remove_pointer_t<typename FDelegateValueMapping::ValueType::Type>>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Key2GarbageCollectionHandle).Remove(FoundValue->Address);

			if (FoundValue->Value != nullptr)
			{
				delete FoundValue->Value;

				FoundValue->Value = nullptr;
			}

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FDelegateRegistry::TDelegateRegistry<std::remove_pointer_t<
		FDelegateRegistry::FDelegateHelperMapping::ValueType::Type>> :
	TDelegateRegistryImplementation<
		FDelegateHelperMapping,
		decltype(&FDelegateRegistry::GarbageCollectionHandle2DelegateHelperAddress),
		&FDelegateRegistry::GarbageCollectionHandle2DelegateHelperAddress,
		decltype(&FDelegateRegistry::DelegateAddress2GarbageCollectionHandle),
		&FDelegateRegistry::DelegateAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FDelegateRegistry::TDelegateRegistry<std::remove_pointer_t<
		FDelegateRegistry::FMulticastDelegateHelperMapping::ValueType::Type>> :
	TDelegateRegistryImplementation<
		FMulticastDelegateHelperMapping,
		decltype(&FDelegateRegistry::GarbageCollectionHandle2MulticastDelegateHelperAddress),
		&FDelegateRegistry::GarbageCollectionHandle2MulticastDelegateHelperAddress,
		decltype(&FDelegateRegistry::MulticastDelegateAddress2GarbageCollectionHandle),
		&FDelegateRegistry::MulticastDelegateAddress2GarbageCollectionHandle
	>
{
};
