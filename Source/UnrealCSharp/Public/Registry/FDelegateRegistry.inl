#pragma once

template <typename T>
auto FDelegateRegistry::GetDelegate(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InGarbageCollectionHandle);

	return FoundDelegateAddress != nullptr ? static_cast<T*>(FoundDelegateAddress->Value) : nullptr;
}
