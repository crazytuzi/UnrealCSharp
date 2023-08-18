#pragma once

template <
	typename Class,
	typename AddressResult,
	typename FMultiRegistry::TMultiMapping<AddressResult>::GarbageCollectionHandle2Address Class::*
	GarbageCollectionHandle2AddressMember,
	typename FMultiRegistry::TMultiMapping<AddressResult>::Address2GarbageCollectionHandle Class::*
	Address2GarbageCollectionHandleMember,
	typename FMultiRegistry::TMultiMapping<AddressResult>::MonoObject2Address Class::*
	MonoObject2AddressMember
>
struct FMultiRegistry::TMultiRegistryImplementation<
		typename FMultiRegistry::TMultiMapping<AddressResult>::GarbageCollectionHandle2Address Class::*,
		GarbageCollectionHandle2AddressMember,
		AddressResult,
		typename FMultiRegistry::TMultiMapping<AddressResult>::Address2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandleMember,
		typename FMultiRegistry::TMultiMapping<AddressResult>::MonoObject2Address Class::*,
		MonoObject2AddressMember
	>
{
	static typename AddressResult::Type* GetMulti(Class* InRegistry,
	                                              const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2AddressMember).Find(InGarbageCollectionHandle);

		return FoundAddress != nullptr ? static_cast<typename AddressResult::Type*>(FoundAddress->MultiValue) : nullptr;
	}

	static typename AddressResult::Type* GetMulti(Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundAddress = (InRegistry->*MonoObject2AddressMember).Find(InMonoObject);

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
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Address2GarbageCollectionHandleMember).Add(InValue, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2AddressMember).Add(
			GarbageCollectionHandle,
			AddressResult{nullptr, static_cast<typename AddressResult::Type*>(InValue), bNeedFree});

		(InRegistry->*MonoObject2AddressMember).Add(
			InMonoObject,
			AddressResult{nullptr, static_cast<typename AddressResult::Type*>(InValue), bNeedFree});

		return true;
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2AddressMember).Find(
			InGarbageCollectionHandle))
		{
			(InRegistry->*Address2GarbageCollectionHandleMember).Remove(FoundAddress->Address);

			if (FoundAddress->bNeedFree)
			{
				FMemory::Free(FoundAddress->Address);

				FoundAddress->Address = nullptr;
			}

			(InRegistry->*MonoObject2AddressMember).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2AddressMember).Remove(InGarbageCollectionHandle);

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
		&FMultiRegistry::SubclassOfAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2SubclassOfAddress),
		&FMultiRegistry::MonoObject2SubclassOfAddress
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
		&FMultiRegistry::WeakObjectPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2WeakObjectPtrAddress),
		&FMultiRegistry::MonoObject2WeakObjectPtrAddress
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
		&FMultiRegistry::LazyObjectPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2LazyObjectPtrAddress),
		&FMultiRegistry::MonoObject2LazyObjectPtrAddress
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
		&FMultiRegistry::SoftObjectPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2SoftObjectPtrAddress),
		&FMultiRegistry::MonoObject2SoftObjectPtrAddress
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
		&FMultiRegistry::ScriptInterfaceAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2ScriptInterfaceAddress),
		&FMultiRegistry::MonoObject2ScriptInterfaceAddress
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
		&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2SoftClassPtrAddress),
		&FMultiRegistry::MonoObject2SoftClassPtrAddress
	>
{
};
