#pragma once

template <
	typename Class,
	typename AddressResult,
	typename FMultiRegistry::TMultiMapping<AddressResult>::GarbageCollectionHandle2Address Class::*
	GarbageCollectionHandle2AddressMember,
	typename FMultiRegistry::TMultiMapping<AddressResult>::Address2GarbageCollectionHandle Class::*
	Address2GarbageCollectionHandleMember
>
struct FMultiRegistry::TMultiRegistryImplementation<
		typename FMultiRegistry::TMultiMapping<AddressResult>::GarbageCollectionHandle2Address Class::*,
		GarbageCollectionHandle2AddressMember,
		AddressResult,
		typename FMultiRegistry::TMultiMapping<AddressResult>::Address2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandleMember
	>
{
	static typename AddressResult::Type* GetMulti(Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2AddressMember).Find(InMonoObject);

		return FoundAddress != nullptr ? static_cast<typename AddressResult::Type*>(FoundAddress->MultiValue) : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const void* InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandleMember).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject, void* InValue, bool bNeedFree = true)
	{
		auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Address2GarbageCollectionHandleMember).Emplace(InValue, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2AddressMember).Emplace(
			MoveTemp(GarbageCollectionHandle),
			AddressResult{nullptr, static_cast<typename AddressResult::Type*>(InValue), bNeedFree});

		return true;
	}

	static bool RemoveReference(Class* InRegistry, const MonoObject* InMonoObject)
	{
		if (const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2AddressMember).Find(InMonoObject))
		{
			(InRegistry->*Address2GarbageCollectionHandleMember).Remove(FoundAddress->Address);

			if (FoundAddress->bNeedFree)
			{
				FMemory::Free(FoundAddress->Address);

				FoundAddress->Address = nullptr;
			}

			(InRegistry->*GarbageCollectionHandle2AddressMember).Remove(InMonoObject);

			return true;
		}

		return false;
	}
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FSubclassOfAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress),
		&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress,
		FSubclassOfAddress,
		decltype(&FMultiRegistry::SubclassOfAddress2GarbageCollectionHandle),
		&FMultiRegistry::SubclassOfAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FWeakObjectPtrAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress,
		FWeakObjectPtrAddress,
		decltype(&FMultiRegistry::WeakObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::WeakObjectPtrAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FLazyObjectPtrAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress,
		FLazyObjectPtrAddress,
		decltype(&FMultiRegistry::LazyObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::LazyObjectPtrAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FSoftObjectPtrAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress,
		FSoftObjectPtrAddress,
		decltype(&FMultiRegistry::SoftObjectPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftObjectPtrAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FScriptInterfaceAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress),
		&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress,
		FScriptInterfaceAddress,
		decltype(&FMultiRegistry::ScriptInterfaceAddress2GarbageCollectionHandle),
		&FMultiRegistry::ScriptInterfaceAddress2GarbageCollectionHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FSoftClassPtrAddress::TIsType<T>::Value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress,
		FSoftClassPtrAddress,
		decltype(&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle
	>
{
};
