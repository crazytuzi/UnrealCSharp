#pragma once

template <
	typename Class,
	typename KeyType,
	typename ValueType,
	typename TValueMapping<KeyType, ValueType>::GarbageCollectionHandle2Value Class::*
	GarbageCollectionHandle2ValueMember,
	typename TValueMapping<KeyType, ValueType>::Value2GarbageCollectionHandle Class::*
	Value2GarbageCollectionHandleMember,
	typename TValueMapping<KeyType, ValueType>::MonoObject2Value Class::*
	MonoObject2ValueMember
>
struct FMultiRegistry::TMultiRegistryImplementation<
		typename TValueMapping<KeyType, ValueType>::GarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2ValueMember,
		KeyType,
		ValueType,
		typename TValueMapping<KeyType, ValueType>::Value2GarbageCollectionHandle Class::*,
		Value2GarbageCollectionHandleMember,
		typename TValueMapping<KeyType, ValueType>::MonoObject2Value Class::*,
		MonoObject2ValueMember
	>
{
	static typename ValueType::Type GetMulti(Class* InRegistry,
	                                         const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).Find(InGarbageCollectionHandle);

		return FoundAddress != nullptr ? static_cast<typename ValueType::Type>(FoundAddress->Value) : nullptr;
	}

	static typename ValueType::Type GetMulti(Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundAddress = (InRegistry->*MonoObject2ValueMember).Find(InMonoObject);

		return FoundAddress != nullptr ? static_cast<typename ValueType::Type>(FoundAddress->Value) : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, const void* InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Value2GarbageCollectionHandleMember).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject, void* InValue, bool bNeedFree = true)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Value2GarbageCollectionHandleMember).Add(InValue, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2ValueMember).Add(
			GarbageCollectionHandle,
			ValueType(nullptr, static_cast<typename ValueType::Type>(InValue), bNeedFree));

		(InRegistry->*MonoObject2ValueMember).Add(
			InMonoObject,
			ValueType(nullptr, static_cast<typename ValueType::Type>(InValue), bNeedFree));

		return true;
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundAddress = (InRegistry->*GarbageCollectionHandle2ValueMember).Find(
			InGarbageCollectionHandle))
		{
			(InRegistry->*Value2GarbageCollectionHandleMember).Remove(FoundAddress->Address);

			if (FoundAddress->bNeedFree)
			{
				FMemory::Free(FoundAddress->Address);

				FoundAddress->Address = nullptr;
			}

			(InRegistry->*MonoObject2ValueMember).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2ValueMember).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FSubclassOfAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress),
		&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress,
		void*,
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
	                                      FMultiRegistry::FWeakObjectPtrAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress,
		void*,
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
	                                      FMultiRegistry::FLazyObjectPtrAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress,
		void*,
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
	                                      FMultiRegistry::FSoftObjectPtrAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress,
		void*,
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
	                                      FMultiRegistry::FScriptInterfaceAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress),
		&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress,
		void*,
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
	                                      FMultiRegistry::FSoftClassPtrAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress,
		void*,
		FSoftClassPtrAddress,
		decltype(&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2SoftClassPtrAddress),
		&FMultiRegistry::MonoObject2SoftClassPtrAddress
	>
{
};
