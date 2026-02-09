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
	static auto GetString(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
		-> typename FStringValueMapping::ValueType::Type
	{
		const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle);

		return FoundValue != nullptr
			       ? static_cast<typename FStringValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static auto GetObject(Class* InRegistry, typename FStringValueMapping::FAddressType InAddress)
		-> MonoObject*
	{
		const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(InAddress);

		return FoundGarbageCollectionHandle != nullptr
			       ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle)
			       : nullptr;
	}

	template <auto IsNeedFree, auto IsMember>
	static auto AddReference(Class* InRegistry, MonoClass* InMonoClass, MonoObject* InMonoObject,
	                         typename FStringValueMapping::FAddressType InAddress)
	{
		const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoClass, InMonoObject, true);

		if constexpr (IsMember)
		{
			(InRegistry->*Address2GarbageCollectionHandle).Add(InAddress, GarbageCollectionHandle);
		}

		(InRegistry->*GarbageCollectionHandle2Value).Add(GarbageCollectionHandle,
		                                                 typename FStringValueMapping::ValueType(
			                                                 static_cast<typename FStringValueMapping::ValueType::Type>(
				                                                 InAddress), IsNeedFree));

		return true;
	}

	static auto RemoveReference(Class* InRegistry, const FGarbageCollectionHandle& InGarbageCollectionHandle)
	{
		if (const auto FoundValue = (InRegistry->*GarbageCollectionHandle2Value).Find(InGarbageCollectionHandle))
		{
			if (const auto FoundGarbageCollectionHandle = (InRegistry->*Address2GarbageCollectionHandle).Find(
				FoundValue->Value))
			{
				if (*FoundGarbageCollectionHandle == InGarbageCollectionHandle)
				{
					(InRegistry->*Address2GarbageCollectionHandle).Remove(FoundValue->Value);
				}
			}

			if (FoundValue->bNeedFree)
			{
				FMemory::Free(FoundValue->Value);

				FoundValue->Value = nullptr;
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

#if UE_F_UTF8_STR_PROPERTY
template <>
struct FStringRegistry::TStringRegistry<FUtf8String> :
	TStringRegistryImplementation<
		FUtf8StringMapping,
		decltype(&FStringRegistry::Utf8StringGarbageCollectionHandle2Address),
		&FStringRegistry::Utf8StringGarbageCollectionHandle2Address,
		decltype(&FStringRegistry::Utf8StringAddress2GarbageCollectionHandle),
		&FStringRegistry::Utf8StringAddress2GarbageCollectionHandle
	>
{
};
#endif

#if UE_F_ANSI_STR_PROPERTY
template <>
struct FStringRegistry::TStringRegistry<FAnsiString> :
	TStringRegistryImplementation<
		FAnsiStringMapping,
		decltype(&FStringRegistry::AnsiStringGarbageCollectionHandle2Address),
		&FStringRegistry::AnsiStringGarbageCollectionHandle2Address,
		decltype(&FStringRegistry::AnsiStringAddress2GarbageCollectionHandle),
		&FStringRegistry::AnsiStringAddress2GarbageCollectionHandle
	>
{
};
#endif

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
