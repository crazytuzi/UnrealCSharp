#pragma once

static bool operator==(const FDelegateAddress& A, const FDelegateAddress& B)
{
	return A.Address == B.Address;
}

static bool operator==(const FDelegateAddress& A, const void* B)
{
	return A.Address == B;
}

static uint32 GetTypeHash(const FDelegateAddress& InDelegateAddress)
{
	return GetTypeHash(InDelegateAddress.Address);
}

template <typename T>
auto FDelegateRegistry::GetDelegate(const MonoObject* InMonoObject)
{
	const auto FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InMonoObject);

	return FoundDelegateAddress != nullptr ? static_cast<T*>(FoundDelegateAddress->DelegateBaseHelper) : nullptr;
}

template <typename T>
auto FDelegateRegistry::GetObject(const T* InDelegate)
{
	for (const auto Pair : DelegateAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InDelegate)
		{
			return static_cast<MonoObject*>(Pair.Value);
		}
	}

	return static_cast<MonoObject*>(nullptr);
}
