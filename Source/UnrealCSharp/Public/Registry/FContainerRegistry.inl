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
auto FContainerRegistry::GetContainer(const MonoObject* InMonoObject)
{
	const auto FoundContainerAddress = GarbageCollectionHandle2ContainerAddress.Find(InMonoObject);

	return FoundContainerAddress != nullptr ? static_cast<T*>(FoundContainerAddress->ContainerHelper) : nullptr;
}

template <typename T>
auto FContainerRegistry::GetContainer(const void* InAddress)
{
	for (const auto& Pair : ContainerAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			return static_cast<T*>(Pair.Key.ContainerHelper);
		}
	}

	return static_cast<T*>(nullptr);
}
