#pragma once

bool operator==(const FBindingAddress& A, const FBindingAddress& B)
{
	return A.Address == B.Address;
}

uint32 GetTypeHash(const FBindingAddress& InBindingAddress)
{
	return GetTypeHash(InBindingAddress.Address);
}

template <typename T>
auto FBindingRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundBindingAddress = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle))
	{
		BindingAddress2GarbageCollectionHandle.Remove(*FoundBindingAddress);

		if (FoundBindingAddress->bNeedFree)
		{
			delete static_cast<T*>(FoundBindingAddress->Address);

			FoundBindingAddress->Address = nullptr;
		}

		GarbageCollectionHandle2BindingAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
