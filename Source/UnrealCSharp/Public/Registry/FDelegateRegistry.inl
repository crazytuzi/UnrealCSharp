#pragma once

#include "Reference/TDelegateReference.h"

template <
	typename Class,
	typename FDelegateValueMapping,
	typename FDelegateValueMapping::GarbageCollectionHandle2Value Class::* GarbageCollectionHandle2ValueMember,
	typename FDelegateValueMapping::Value2GarbageCollectionHandle Class::* Value2GarbageCollectionHandleMember
>
struct FDelegateRegistry::TDelegateRegistryImplementation<
		FDelegateValueMapping,
		typename FDelegateValueMapping::GarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2ValueMember,
		typename FDelegateValueMapping::Value2GarbageCollectionHandle Class::*,
		Value2GarbageCollectionHandleMember
	>
{
	static typename FDelegateValueMapping::ValueType::Type GetDelegate(Class* InRegistry,
	                                                                   const FGarbageCollectionHandle&
	                                                                   InGarbageCollectionHandle)
	{
		const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).Find(InGarbageCollectionHandle);

		return FoundAddress != nullptr ? FoundAddress->Value : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const void* InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Value2GarbageCollectionHandleMember).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, void* InAddress,
	                         typename FDelegateValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Value2GarbageCollectionHandleMember).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2ValueMember).Add(GarbageCollectionHandle,
		                                                       typename FDelegateValueMapping::ValueType(
			                                                       InAddress, InValue));

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner, void* InAddress,
	                         typename FDelegateValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Value2GarbageCollectionHandleMember).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2ValueMember).Add(GarbageCollectionHandle,
		                                                       typename FDelegateValueMapping::ValueType(
			                                                       InAddress, InValue));

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TDelegateReference<typename TRemovePointer<typename FDelegateValueMapping::ValueType::Type>::Type>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).
			Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Value2GarbageCollectionHandleMember).Remove(FoundAddress->Address);

			if (FoundAddress->Value != nullptr)
			{
				delete FoundAddress->Value;

				FoundAddress->Value = nullptr;
			}

			(InRegistry->*GarbageCollectionHandle2ValueMember).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FDelegateRegistry::TDelegateRegistry<TRemovePointer<
		FDelegateRegistry::FDelegateHelperMapping::ValueType::Type>::Type> :
	TDelegateRegistryImplementation<
		FDelegateHelperMapping,
		decltype(&FDelegateRegistry::GarbageCollectionHandle2DelegateHelperAddress),
		&FDelegateRegistry::GarbageCollectionHandle2DelegateHelperAddress,
		decltype(&FDelegateRegistry::DelegateHelperAddress2GarbageCollectionHandle),
		&FDelegateRegistry::DelegateHelperAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FDelegateRegistry::TDelegateRegistry<TRemovePointer<
		FDelegateRegistry::FMulticastDelegateHelperMapping::ValueType::Type>::Type> :
	TDelegateRegistryImplementation<
		FMulticastDelegateHelperMapping,
		decltype(&FDelegateRegistry::GarbageCollectionHandle2MulticastDelegateHelperAddress),
		&FDelegateRegistry::GarbageCollectionHandle2MulticastDelegateHelperAddress,
		decltype(&FDelegateRegistry::MulticastDelegateHelperAddress2GarbageCollectionHandle),
		&FDelegateRegistry::MulticastDelegateHelperAddress2GarbageCollectionHandle
	>
{
};
