#pragma once

template <
	typename Class,
	typename FStringValueMapping,
	typename FStringValueMapping::FGarbageCollectionHandle2Value Class::* GarbageCollectionHandle2Value,
	typename FStringValueMapping::FAddress2GarbageCollectionHandle Class::* Address2GarbageCollectionHandle
>
struct FStringRegistry::TStringRegistryImplementation<
		FStringValueMapping,
		typename FStringValueMapping::FGarbageCollectionHandle2Value Class::*,
		GarbageCollectionHandle2Value,
		typename FStringValueMapping::FAddress2GarbageCollectionHandle Class::*,
		Address2GarbageCollectionHandle
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

	static MonoObject* GetObject(Class* InRegistry, typename FStringValueMapping::FAddressType InAddress)
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	static bool AddReference(Class* InRegistry, MonoObject* InMonoObject,
	                         typename FStringValueMapping::FAddressType InAddress,
	                         bool bNeedFree = true)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

		if (bNeedFree == false)
		{
			(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);
		}

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FStringValueMapping::ValueType(
			                                                 static_cast<typename FStringValueMapping::ValueType::Type>(
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

template <>
struct FStringRegistry::TStringRegistry<FName> :
	TStringRegistryImplementation<
		FNameMapping,
		decltype(&FStringRegistry::NameGarbageCollectionHandle2Address),
		&FStringRegistry::NameGarbageCollectionHandle2Address,
		decltype(&FStringRegistry::NameAddress2GarbageCollectionHandle),
		&FStringRegistry::NameAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FStringRegistry::TStringRegistry<FString> :
	TStringRegistryImplementation<
		FStringMapping,
		decltype(&FStringRegistry::StringGarbageCollectionHandle2Address),
		&FStringRegistry::StringGarbageCollectionHandle2Address,
		decltype(&FStringRegistry::StringAddress2GarbageCollectionHandle),
		&FStringRegistry::StringAddress2GarbageCollectionHandle
	>
{
};

template <>
struct FStringRegistry::TStringRegistry<FText> :
	TStringRegistryImplementation<
		FTextMapping,
		decltype(&FStringRegistry::TextGarbageCollectionHandle2Address),
		&FStringRegistry::TextGarbageCollectionHandle2Address,
		decltype(&FStringRegistry::TextAddress2GarbageCollectionHandle),
		&FStringRegistry::TextAddress2GarbageCollectionHandle
	>
{
};
