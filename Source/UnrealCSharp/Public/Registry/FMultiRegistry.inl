#pragma once

template <
	typename Class,
	typename FMultiValueMapping,
	typename FMultiValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FMultiValueMapping::FKey2GarbageCollectionHandle Class::* Key2GarbageCollectionHandle,
	typename FMultiValueMapping::FMonoObject2Value Class::* MonoObject2Value
>
struct FMultiRegistry::TMultiRegistryImplementation<
		FMultiValueMapping,
		typename FMultiValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FMultiValueMapping::FKey2GarbageCollectionHandle Class::*,
		Key2GarbageCollectionHandle,
		typename FMultiValueMapping::FMonoObject2Value Class::*,
		MonoObject2Value
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

	static typename FMultiValueMapping::ValueType::Type GetMulti(Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundValue = (InRegistry->*MonoObject2Value).Find(InMonoObject);

		return FoundValue != nullptr
			       ? static_cast<typename FMultiValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, typename FMultiValueMapping::KeyType InKey)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Key2GarbageCollectionHandle).Find(InKey);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject, typename FMultiValueMapping::KeyType InKey,
	                         bool bNeedFree = true)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(InKey, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FMultiValueMapping::ValueType(
			                                                 static_cast<typename FMultiValueMapping::ValueType::Type>(
				                                                 InKey), bNeedFree));

		(InRegistry->*MonoObject2Value).Add(InMonoObject,
		                                    typename FMultiValueMapping::ValueType(
			                                    static_cast<typename FMultiValueMapping::ValueType::Type>(InKey),
			                                    bNeedFree));

		return true;
	}

	static bool RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			(InRegistry->*Key2GarbageCollectionHandle).Remove(FoundValue->Value);

			if (FoundValue->bNeedFree)
			{
				FMemory::Free(FoundValue->Value);

				FoundValue->Value = nullptr;
			}

			(InRegistry->*MonoObject2Value).Remove(InGarbageCollectionHandle);

			(InRegistry->*GarbageCollectionHandle2Value).Remove(InGarbageCollectionHandle);

			return true;
		}

		return false;
	}
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, typename TEnableIf<
	                                      FMultiRegistry::FSubclassOfAddress::TIsType<T>::value, T>::Type> :
	TMultiRegistryImplementation<
		FSubclassOfMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress),
		&FMultiRegistry::GarbageCollectionHandle2SubclassOfAddress,
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
		FWeakObjectPtrMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2WeakObjectPtrAddress,
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
		FLazyObjectPtrMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2LazyObjectPtrAddress,
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
		FSoftObjectPtrMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftObjectPtrAddress,
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
		FScriptInterfaceMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress),
		&FMultiRegistry::GarbageCollectionHandle2ScriptInterfaceAddress,
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
		FSoftClassPtrMapping,
		decltype(&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress),
		&FMultiRegistry::GarbageCollectionHandle2SoftClassPtrAddress,
		decltype(&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle),
		&FMultiRegistry::SoftClassPtrAddress2GarbageCollectionHandle,
		decltype(&FMultiRegistry::MonoObject2SoftClassPtrAddress),
		&FMultiRegistry::MonoObject2SoftClassPtrAddress
	>
{
};
