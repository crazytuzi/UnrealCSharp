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
auto FBindingRegistry::GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundStructAddress = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle);

	return FoundStructAddress != nullptr ? static_cast<T*>(FoundStructAddress->AddressWrapper->GetValue()) : nullptr;
}

template <typename T>
auto FBindingRegistry::GetBinding(const MonoObject* InMonoObject)
{
	const auto FoundStructAddress = MonoObject2BindingAddress.Find(InMonoObject);

	return FoundStructAddress != nullptr ? static_cast<T*>(FoundStructAddress->AddressWrapper->GetValue()) : nullptr;
}

template <typename T>
auto FBindingRegistry::AddReference(const T* InObject, MonoObject* InMonoObject, const bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), GarbageCollectionHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           FBindingAddress{BindingAddressWrapper, bNeedFree});

	MonoObject2BindingAddress.Add(InMonoObject,
	                              FBindingAddress{BindingAddressWrapper, bNeedFree});

	return true;
}
