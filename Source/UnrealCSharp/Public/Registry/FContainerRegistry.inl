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
	typename FContainerValueMapping::GarbageCollectionHandle2Value Class::* GarbageCollectionHandle2ValueMember,
	typename FContainerValueMapping::Value2GarbageCollectionHandle Class::* Value2GarbageCollectionHandleMember,
	typename FContainerValueMapping::MonoObject2Value Class::* MonoObject2ValueMember,
	typename FContainerValueMapping::Address2GarbageCollectionHandle Class::* Address2GarbageCollectionHandleMember
>
struct FContainerRegistry::TContainerRegistryImplementation<
		FContainerValueMapping,
		typename FContainerValueMapping::GarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2ValueMember,
		typename FContainerValueMapping::Value2GarbageCollectionHandle Class::*,
		Value2GarbageCollectionHandleMember,
		typename FContainerValueMapping::MonoObject2Value Class::*,
		MonoObject2ValueMember,
		typename FContainerValueMapping::Address2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandleMember
	>
{
	static typename FContainerValueMapping::ValueType::Type GetContainer(
		Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).Find(InGarbageCollectionHandle);

		return FoundAddress != nullptr
			       ? static_cast<typename FContainerValueMapping::ValueType::Type>(FoundAddress->Value)
			       : nullptr;
	}

	static typename FContainerValueMapping::ValueType::Type GetContainer(
		Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundAddress = (InRegistry->*MonoObject2ValueMember).Find(InMonoObject);

		return FoundAddress != nullptr
			       ? static_cast<typename FContainerValueMapping::ValueType::Type>(FoundAddress->Value)
			       : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const void* InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandleMember).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, void* InAddress,
	                         typename FContainerValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Value2GarbageCollectionHandleMember).Add(
			typename FContainerValueMapping::KeyType(InAddress, InValue), GarbageCollectionHandle);

		if (InAddress != nullptr)
		{
			(InRegistry->*Address2GarbageCollectionHandleMember).Add(InAddress, GarbageCollectionHandle);
		}

		(InRegistry->*GarbageCollectionHandle2ValueMember).Add(GarbageCollectionHandle,
		                                                       typename FContainerValueMapping::ValueType(
			                                                       InAddress, InValue));

		(InRegistry->*MonoObject2ValueMember).Add(InMonoObject,
		                                          typename FContainerValueMapping::ValueType(InAddress, InValue));

		return true;
	}

	static bool AddReference(Class* InRegistry, const FGarbageCollectionHandle& InOwner, void* InAddress,
	                         typename FContainerValueMapping::ValueType::Type InValue, MonoObject* InMonoObject)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

		(InRegistry->*Value2GarbageCollectionHandleMember).Add(
			typename FContainerValueMapping::KeyType(InAddress, InValue), GarbageCollectionHandle);

		(InRegistry->*Address2GarbageCollectionHandleMember).Add(InAddress, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2ValueMember).Add(GarbageCollectionHandle,
		                                                       typename FContainerValueMapping::ValueType(
			                                                       InAddress, InValue));

		(InRegistry->*MonoObject2ValueMember).Add(InMonoObject,
		                                          typename FContainerValueMapping::ValueType(InAddress, InValue));

		return FCSharpEnvironment::GetEnvironment().AddReference(
			InOwner,
			new TContainerReference<typename TRemovePointer<typename FContainerValueMapping::ValueType::Type>::Type>(
				GarbageCollectionHandle));
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).
			Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Value2GarbageCollectionHandleMember).Remove(*FoundAddress);

			if (FoundAddress->Address != nullptr)
			{
				(InRegistry->*Address2GarbageCollectionHandleMember).Remove(FoundAddress->Address);
			}

			if (FoundAddress->Value != nullptr)
			{
				delete FoundAddress->Value;

				FoundAddress->Value = nullptr;
			}

			(InRegistry->*MonoObject2ValueMember).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2ValueMember).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FContainerRegistry::TContainerRegistry<TRemovePointer<
		FContainerRegistry::FArrayHelperValueMapping::KeyType::Type>::Type> :
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
struct FContainerRegistry::TContainerRegistry<TRemovePointer<
		FContainerRegistry::FMapHelperValueMapping::KeyType::Type>::Type> :
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
struct FContainerRegistry::TContainerRegistry<TRemovePointer<
		FContainerRegistry::FSetHelperValueMapping::KeyType::Type>::Type> :
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
