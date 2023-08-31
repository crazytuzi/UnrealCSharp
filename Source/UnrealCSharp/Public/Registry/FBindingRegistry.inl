#pragma once

bool operator==(const FBindingAddress& A, const FBindingAddress& B)
{
	return A.AddressWrapper == B.AddressWrapper;
}

uint32 GetTypeHash(const FBindingAddress& InBindingAddress)
{
	return GetTypeHash(InBindingAddress.AddressWrapper);
}

template <typename T>
auto FBindingRegistry::AddReference(const T* InObject, MonoObject* InMonoObject, const bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), GarbageCollectionHandle);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           FBindingAddress{new TBindingAddressWrapper(InObject), bNeedFree});

	return true;
}
