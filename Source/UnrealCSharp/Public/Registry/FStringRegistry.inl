#pragma once

#include "Domain/FDomain.h"
#include "Reflection/FClassReflection.h"

template <
	typename Class,
	typename FStringValueMapping,
	typename FStringValueMapping::FManagedHandle2Value Class::* ManagedHandle2Value,
	typename FStringValueMapping::FAddress2ManagedHandle Class::* Address2ManagedHandle
>
struct FStringRegistry::TStringRegistryImplementation<
		FStringValueMapping,
		typename FStringValueMapping::FManagedHandle2Value Class::*,
		ManagedHandle2Value,
		typename FStringValueMapping::FAddress2ManagedHandle Class::*,
		Address2ManagedHandle
	>
{
	static auto GetString(Class* InRegistry, const IManagedHandle InManagedHandle)
		-> typename FStringValueMapping::ValueType::Type
	{
		const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle);

		return FoundValue != nullptr
			       ? static_cast<typename FStringValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static auto GetObject(Class* InRegistry, typename FStringValueMapping::FAddressType InAddress)
		-> IManagedHandle
	{
		const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(InAddress);

		return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
	}

	template <auto IsNeedFree, auto IsMember>
	static auto AddReference(Class* InRegistry, FClassReflection* InClass, const IManagedHandle InManagedHandle,
	                         typename FStringValueMapping::FAddressType InAddress)
	{
		const auto ManagedHandle = InClass->NewWeakRefGCHandle(InManagedHandle, true);

		if constexpr (IsMember)
		{
			(InRegistry->*Address2ManagedHandle).Add(InAddress, ManagedHandle);
		}

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle,
		                                       typename FStringValueMapping::ValueType(
			                                       static_cast<typename FStringValueMapping::ValueType::Type>(
				                                       InAddress), IsNeedFree));

		return true;
	}

	static auto RemoveReference(Class* InRegistry, const IManagedHandle InManagedHandle)
	{
		if (const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle))
		{
			if (const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(FoundValue->Value))
			{
				if (*FoundManagedHandle == InManagedHandle)
				{
					(InRegistry->*Address2ManagedHandle).Remove(FoundValue->Value);
				}
			}

			if (FoundValue->bNeedFree)
			{
				FMemory::Free(FoundValue->Value);

				FoundValue->Value = nullptr;
			}

			(InRegistry->*ManagedHandle2Value).Remove(InManagedHandle);

			return true;
		}

		return false;
	}
};

template <>
struct FStringRegistry::TStringRegistry<FName> :
	TStringRegistryImplementation<
		FNameMapping,
		decltype(&FStringRegistry::NameManagedHandle2Address),
		&FStringRegistry::NameManagedHandle2Address,
		decltype(&FStringRegistry::NameAddress2ManagedHandle),
		&FStringRegistry::NameAddress2ManagedHandle
	>
{
};

template <>
struct FStringRegistry::TStringRegistry<FString> :
	TStringRegistryImplementation<
		FStringMapping,
		decltype(&FStringRegistry::StringManagedHandle2Address),
		&FStringRegistry::StringManagedHandle2Address,
		decltype(&FStringRegistry::StringAddress2ManagedHandle),
		&FStringRegistry::StringAddress2ManagedHandle
	>
{
};

#if UE_F_UTF8_STR_PROPERTY
template <>
struct FStringRegistry::TStringRegistry<FUtf8String> :
	TStringRegistryImplementation<
		FUtf8StringMapping,
		decltype(&FStringRegistry::Utf8StringManagedHandle2Address),
		&FStringRegistry::Utf8StringManagedHandle2Address,
		decltype(&FStringRegistry::Utf8StringAddress2ManagedHandle),
		&FStringRegistry::Utf8StringAddress2ManagedHandle
	>
{
};
#endif

#if UE_F_ANSI_STR_PROPERTY
template <>
struct FStringRegistry::TStringRegistry<FAnsiString> :
	TStringRegistryImplementation<
		FAnsiStringMapping,
		decltype(&FStringRegistry::AnsiStringManagedHandle2Address),
		&FStringRegistry::AnsiStringManagedHandle2Address,
		decltype(&FStringRegistry::AnsiStringAddress2ManagedHandle),
		&FStringRegistry::AnsiStringAddress2ManagedHandle
	>
{
};
#endif

template <>
struct FStringRegistry::TStringRegistry<FText> :
	TStringRegistryImplementation<
		FTextMapping,
		decltype(&FStringRegistry::TextManagedHandle2Address),
		&FStringRegistry::TextManagedHandle2Address,
		decltype(&FStringRegistry::TextAddress2ManagedHandle),
		&FStringRegistry::TextAddress2ManagedHandle
	>
{
};
