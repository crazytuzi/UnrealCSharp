#pragma once

template <
	typename Class,
	typename FStringValueMapping,
	typename FStringValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FStringValueMapping::FKey2GarbageCollectionHandle Class::* Key2GarbageCollectionHandle,
	typename FStringValueMapping::FMonoObject2Value Class::* MonoObject2Value
>
struct FStringRegistry::TStringRegistryImplementation<
		FStringValueMapping,
		typename FStringValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FStringValueMapping::FKey2GarbageCollectionHandle Class::*,
		Key2GarbageCollectionHandle,
		typename FStringValueMapping::FMonoObject2Value Class::*,
		MonoObject2Value
	>
{
	static typename FStringValueMapping::ValueType::Type GetString(Class* InRegistry,
	                                                               const FGarbageCollectionHandle&
	                                                               InGarbageCollectionHandle)
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr
			       ? static_cast<typename FStringValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static typename FStringValueMapping::ValueType::Type GetString(Class* InRegistry, const MonoObject* InMonoObject)
	{
		const auto FoundValue = (InRegistry->*MonoObject2Value).Find(InMonoObject);

		return FoundValue != nullptr
			       ? static_cast<typename FStringValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static MonoObject* GetObject(Class* InRegistry, typename FStringValueMapping::KeyType InKey)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Key2GarbageCollectionHandle).Find(InKey);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject, typename FStringValueMapping::KeyType InKey,
	                         bool bNeedFree = true)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		(InRegistry->*Key2GarbageCollectionHandle).Add(InKey, GarbageCollectionHandle);

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FStringValueMapping::ValueType(
			                                                 static_cast<typename FStringValueMapping::ValueType::Type>(
				                                                 InKey), bNeedFree));

		(InRegistry->*MonoObject2Value).Add(InMonoObject,
		                                    typename FStringValueMapping::ValueType(
			                                    static_cast<typename FStringValueMapping::ValueType::Type>(InKey),
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

template <>
struct FStringRegistry::TStringRegistry<FName> :
	TStringRegistryImplementation<
		FNameMapping,
		decltype(&FStringRegistry::GarbageCollectionHandle2NameAddress),
		&FStringRegistry::GarbageCollectionHandle2NameAddress,
		decltype(&FStringRegistry::NameAddress2GarbageCollectionHandle),
		&FStringRegistry::NameAddress2GarbageCollectionHandle,
		decltype(&FStringRegistry::MonoObject2NameAddress),
		&FStringRegistry::MonoObject2NameAddress
	>
{
};

template <>
struct FStringRegistry::TStringRegistry<FString> :
	TStringRegistryImplementation<
		FStringMapping,
		decltype(&FStringRegistry::GarbageCollectionHandle2StringAddress),
		&FStringRegistry::GarbageCollectionHandle2StringAddress,
		decltype(&FStringRegistry::StringAddress2GarbageCollectionHandle),
		&FStringRegistry::StringAddress2GarbageCollectionHandle,
		decltype(&FStringRegistry::MonoObject2StringAddress),
		&FStringRegistry::MonoObject2StringAddress
	>
{
};

template <>
struct FStringRegistry::TStringRegistry<FText> :
	TStringRegistryImplementation<
		FTextMapping,
		decltype(&FStringRegistry::GarbageCollectionHandle2TextAddress),
		&FStringRegistry::GarbageCollectionHandle2TextAddress,
		decltype(&FStringRegistry::TextAddress2GarbageCollectionHandle),
		&FStringRegistry::TextAddress2GarbageCollectionHandle,
		decltype(&FStringRegistry::MonoObject2TextAddress),
		&FStringRegistry::MonoObject2TextAddress
	>
{
};
