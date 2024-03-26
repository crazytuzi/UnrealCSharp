﻿#pragma once

template <
	typename Class,
	typename FMultiValueMapping,
	typename FMultiValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FMultiValueMapping::FAddress2GarbageCollectionHandle Class::* Address2GarbageCollectionHandle
>
struct FMultiRegistry::TMultiRegistryImplementation<
		FMultiValueMapping,
		typename FMultiValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FMultiValueMapping::FAddress2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandle
	>
{
	static typename FMultiValueMapping::ValueType::Type GetMulti(Class* InRegistry,
	                                                             const FGarbageCollectionHandle&
	                                                             InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr
			       ? static_cast<typename FMultiValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, typename FMultiValueMapping::FAddressType InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject,
	                         typename FMultiValueMapping::FAddressType InAddress,
	                         bool bNeedFree = true)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		if (bNeedFree == false)
		{
			(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);
		}

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FMultiValueMapping::ValueType(
			                                                 static_cast<typename FMultiValueMapping::ValueType::Type>(
				                                                 InAddress), bNeedFree));

		return true;
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			if (FoundValue->bNeedFree)
			{
				FMemory::Free(FoundValue->Value);

				FoundValue->Value = nullptr;
			}
			else
			{
				(InRegistry->*Address2GarbageCollectionHandle).Remove(FoundValue->Value);
			}

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSubclassOfAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSubclassOfMapping,
		decltype(&FMultiRegistry::SubclassOfGarbageCollectionHandle2Address),
		&FMultiRegistry::SubclassOfGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::SubclassOfAddress2GarbageCollectionHandle),
		&FMultiRegistry::SubclassOfAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FWeakObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FWeakObjectPtrMapping,
		decltype(&FMultiRegistry::WeakObjectPtrGarbageCollectionHandle2Address),
		&FMultiRegistry::WeakObjectPtrGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::WeakObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::WeakObjectPtrAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FLazyObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FLazyObjectPtrMapping,
		decltype(&FMultiRegistry::LazyObjectPtrGarbageCollectionHandle2Address),
		&FMultiRegistry::LazyObjectPtrGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::LazyObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::LazyObjectPtrAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSoftObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSoftObjectPtrMapping,
		decltype(&FMultiRegistry::SoftObjectPtrGarbageCollectionHandle2Address),
		&FMultiRegistry::SoftObjectPtrGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::SoftObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftObjectPtrAddress2GarbageCollectionHandle

	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FScriptInterfaceAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FScriptInterfaceMapping,
		decltype(&FMultiRegistry::ScriptInterfaceGarbageCollectionHandle2Address),
		&FMultiRegistry::ScriptInterfaceGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::ScriptInterfaceAddress2GarbageCollectionHandle),
		&FMultiRegistry::ScriptInterfaceAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSoftClassPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSoftClassPtrMapping,
		decltype(&FMultiRegistry::SoftClassPtrGarbageCollectionHandle2Address),
		&FMultiRegistry::SoftClassPtrGarbageCollectionHandle2Address,
		decltype(&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle
	>
{
};
