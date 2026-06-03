#pragma once

#include "Domain/FDomain.h"
#include "Reflection/FClassReflection.h"

template <
	typename Class,
	typename FMultiValueMapping,
	typename FMultiValueMapping::FManagedHandle2Value Class::* ManagedHandle2Value,
	typename FMultiValueMapping::FAddress2ManagedHandle Class::* Address2ManagedHandle
>
struct FMultiRegistry::TMultiRegistryImplementation<
		FMultiValueMapping,
		typename FMultiValueMapping::FManagedHandle2Value Class::*,
		ManagedHandle2Value,
		typename FMultiValueMapping::FAddress2ManagedHandle Class::*,
		Address2ManagedHandle
	>
{
	static auto GetMulti(Class* InRegistry, const IManagedHandle InManagedHandle)
		-> typename FMultiValueMapping::ValueType::Type
	{
		const auto FoundValue = (InRegistry->*ManagedHandle2Value).Find(InManagedHandle);

		return FoundValue != nullptr
			       ? static_cast<typename FMultiValueMapping::ValueType::Type>(FoundValue->Value)
			       : nullptr;
	}

	static auto GetObject(Class* InRegistry, typename FMultiValueMapping::FAddressType InAddress)
		-> IManagedHandle
	{
		const auto FoundManagedHandle = (InRegistry->*Address2ManagedHandle).Find(InAddress);

		return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
	}

	template <auto IsNeedFree, auto IsMember>
	static auto AddReference(Class* InRegistry, FClassReflection* InClass, IManagedHandle InScriptHandle,
	                         typename FMultiValueMapping::FAddressType InAddress)
	{
		const auto ManagedHandle = InClass->NewWeakRefGCHandle(InScriptHandle, true);

		if constexpr (IsMember)
		{
			(InRegistry->*Address2ManagedHandle).Add(InAddress, ManagedHandle);
		}

		(InRegistry->*ManagedHandle2Value).Add(ManagedHandle,
		                                       typename FMultiValueMapping::ValueType(
			                                       static_cast<typename FMultiValueMapping::ValueType::Type>(
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

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSubclassOfAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSubclassOfMapping,
		decltype(&FMultiRegistry::SubclassOfManagedHandle2Address),
		&FMultiRegistry::SubclassOfManagedHandle2Address,
		decltype(&FMultiRegistry::SubclassOfAddress2ManagedHandle),
		&FMultiRegistry::SubclassOfAddress2ManagedHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FWeakObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FWeakObjectPtrMapping,
		decltype(&FMultiRegistry::WeakObjectPtrManagedHandle2Address),
		&FMultiRegistry::WeakObjectPtrManagedHandle2Address,
		decltype(&FMultiRegistry::WeakObjectPtrAddress2ManagedHandle),
		&FMultiRegistry::WeakObjectPtrAddress2ManagedHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FLazyObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FLazyObjectPtrMapping,
		decltype(&FMultiRegistry::LazyObjectPtrManagedHandle2Address),
		&FMultiRegistry::LazyObjectPtrManagedHandle2Address,
		decltype(&FMultiRegistry::LazyObjectPtrAddress2ManagedHandle),
		&FMultiRegistry::LazyObjectPtrAddress2ManagedHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSoftObjectPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSoftObjectPtrMapping,
		decltype(&FMultiRegistry::SoftObjectPtrManagedHandle2Address),
		&FMultiRegistry::SoftObjectPtrManagedHandle2Address,
		decltype(&FMultiRegistry::SoftObjectPtrAddress2ManagedHandle),
		&FMultiRegistry::SoftObjectPtrAddress2ManagedHandle

	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FScriptInterfaceAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FScriptInterfaceMapping,
		decltype(&FMultiRegistry::ScriptInterfaceManagedHandle2Address),
		&FMultiRegistry::ScriptInterfaceManagedHandle2Address,
		decltype(&FMultiRegistry::ScriptInterfaceAddress2ManagedHandle),
		&FMultiRegistry::ScriptInterfaceAddress2ManagedHandle
	>
{
};

template <typename T>
struct FMultiRegistry::TMultiRegistry<T, std::enable_if_t<
	                                      FMultiRegistry::FSoftClassPtrAddress::TIsType<T>::value, T>> :
	TMultiRegistryImplementation<
		FSoftClassPtrMapping,
		decltype(&FMultiRegistry::SoftClassPtrManagedHandle2Address),
		&FMultiRegistry::SoftClassPtrManagedHandle2Address,
		decltype(&FMultiRegistry::SoftClassPtrAddress2ManagedHandle),
		&FMultiRegistry::SoftClassPtrAddress2ManagedHandle
	>
{
};
