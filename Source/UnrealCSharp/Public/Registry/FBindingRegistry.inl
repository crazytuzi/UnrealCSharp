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
	const auto FoundValue = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle);

	return FoundValue != nullptr ? static_cast<T*>(FoundValue->AddressWrapper->GetValue()) : nullptr;
}

template <typename T>
auto FBindingRegistry::GetBinding(const MonoObject* InMonoObject)
{
	const auto FoundValue = MonoObject2BindingAddress.Find(InMonoObject);

	return FoundValue != nullptr ? static_cast<T*>(FoundValue->AddressWrapper->GetValue()) : nullptr;
}

template <typename T>
auto FBindingRegistry::AddReference(const T* InObject, MonoObject* InMonoObject, const bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(static_cast<void*>(const_cast<T*>(InObject)), GarbageCollectionHandle);

	auto BindingAddressWrapper = new TBindingAddressWrapper(InObject);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           FBindingValueMapping::ValueType(BindingAddressWrapper, bNeedFree));

	MonoObject2BindingAddress.Add(InMonoObject, FBindingValueMapping::ValueType(BindingAddressWrapper, bNeedFree));

	return true;
}
