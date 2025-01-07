#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Reference/FBindingReference.h"

template <typename T>
auto FBindingRegistry::GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundValue = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle);

	return FoundValue != nullptr ? static_cast<T*>(FoundValue->AddressWrapper->Value) : nullptr;
}

template <typename T, auto IsNeedFree>
auto FBindingRegistry::AddReference(const T* InObject, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           FBindingValueMapping::ValueType(BindingAddressWrapper, IsNeedFree));

	return true;
}

template <typename T>
auto FBindingRegistry::AddReference(const FGarbageCollectionHandle& InOwner, const T* InObject,
                                    MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), GarbageCollectionHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           FBindingValueMapping::ValueType(BindingAddressWrapper, false));

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FBindingReference(GarbageCollectionHandle));
}
