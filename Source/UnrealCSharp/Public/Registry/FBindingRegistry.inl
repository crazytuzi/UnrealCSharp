#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Reference/FBindingReference.h"

template <typename T>
auto FBindingRegistry::GetBinding(const IManagedHandle InManagedHandle)
{
	const auto FoundValue = ManagedHandle2BindingAddress.Find(InManagedHandle);

	return FoundValue != nullptr ? static_cast<T*>(FoundValue->AddressWrapper->Value) : nullptr;
}

template <typename T, auto IsNeedFree>
auto FBindingRegistry::AddReference(const T* InObject, FClassReflection* InClass, const IManagedHandle InManagedHandle)
{
	const auto ManagedHandle = InClass->NewWeakRefGCHandle(InManagedHandle, true);

	BindingAddress2ManagedHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), ManagedHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	ManagedHandle2BindingAddress.Add(ManagedHandle, FBindingValueMapping::ValueType(BindingAddressWrapper, IsNeedFree));

	return true;
}

template <typename T>
auto FBindingRegistry::AddReference(const IManagedHandle InOwner, const T* InObject,
                                    FClassReflection* InClass, const IManagedHandle InManagedHandle)
{
	const auto ManagedHandle = InClass->NewGCHandle(InManagedHandle, true);

	BindingAddress2ManagedHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), ManagedHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	ManagedHandle2BindingAddress.Add(ManagedHandle, FBindingValueMapping::ValueType(BindingAddressWrapper, false));

	return FCSharpEnvironment::GetEnvironment().AddReference(InOwner, new FBindingReference(ManagedHandle));
}
