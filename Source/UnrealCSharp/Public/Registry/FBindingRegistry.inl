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
	BindingAddress2ManagedHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), InManagedHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	ManagedHandle2BindingAddress.Add(InManagedHandle,
	                                 FBindingValueMapping::ValueType(BindingAddressWrapper, IsNeedFree));

	return true;
}

template <typename T>
auto FBindingRegistry::AddReference(const IManagedHandle InOwner, const T* InObject,
                                    FClassReflection* InClass, const IManagedHandle InManagedHandle)
{
	BindingAddress2ManagedHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), InManagedHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	ManagedHandle2BindingAddress.Add(InManagedHandle, FBindingValueMapping::ValueType(BindingAddressWrapper, false));

	return FCSharpEnvironment::GetEnvironment().AddReference(InOwner, new FBindingReference(InManagedHandle));
}
