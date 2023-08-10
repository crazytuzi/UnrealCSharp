#pragma once

static bool operator==(const FContainerAddress& A, const FContainerAddress& B)
{
	return A.Address == B.Address && A.ContainerHelper == B.ContainerHelper;
}

static bool operator==(const FContainerAddress& A, const void* B)
{
	return A.Address == B;
}

static uint32 GetTypeHash(const FContainerAddress& InContainerAddress)
{
	return GetTypeHash(InContainerAddress.Address != nullptr
		                   ? InContainerAddress.Address
		                   : InContainerAddress.ContainerHelper);
}

template <typename T>
auto FContainerRegistry::GetContainer(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundContainerAddress = GarbageCollectionHandle2ContainerAddress.Find(InGarbageCollectionHandle);

	return FoundContainerAddress != nullptr ? static_cast<T*>(FoundContainerAddress->ContainerHelper) : nullptr;
}

template <typename T>
auto FContainerRegistry::GetContainer(const MonoObject* InMonoObject)
{
	return GetContainer<T>(MonoObject2GarbageCollectionHandleMap[InMonoObject]);
}
