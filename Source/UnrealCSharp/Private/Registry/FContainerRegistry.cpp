#include "Registry/FContainerRegistry.h"
#include "Reference/FContainerReference.h"
#include "Environment/FCSharpEnvironment.h"

FContainerRegistry::FContainerRegistry()
{
	Initialize();
}

FContainerRegistry::~FContainerRegistry()
{
	Deinitialize();
}

void FContainerRegistry::Initialize()
{
}

void FContainerRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2ContainerAddress.Get())
	{
		if (Pair.Value.ContainerHelper != nullptr)
		{
			delete Pair.Value.ContainerHelper;

			Pair.Value.ContainerHelper = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2ContainerAddress.Empty();

	ContainerAddress2GarbageCollectionHandle.Empty();

	Address2GarbageCollectionHandle.Empty();

	MonoObject2GarbageCollectionHandleMap.Empty();
}

MonoObject* FContainerRegistry::GetObject(const void* InAddress)
{
	if (const auto GarbageCollectionHandle = Address2GarbageCollectionHandle.Find(InAddress))
	{
		return *GarbageCollectionHandle;
	}

	return nullptr;
}

bool FContainerRegistry::AddReference(void* InAddress, void* InContainer, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	ContainerAddress2GarbageCollectionHandle.Add(
		FContainerAddress{InAddress, static_cast<FContainerHelper*>(InContainer)}, GarbageCollectionHandle);

	if (InAddress != nullptr)
	{
		Address2GarbageCollectionHandle.Add(InAddress, GarbageCollectionHandle);
	}

	GarbageCollectionHandle2ContainerAddress.Add(GarbageCollectionHandle,
	                                             FContainerAddress{
		                                             InAddress, static_cast<FContainerHelper*>(InContainer)
	                                             });

	MonoObject2GarbageCollectionHandleMap.Add(InMonoObject, GarbageCollectionHandle);

	return true;
}

bool FContainerRegistry::AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
                                      MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	ContainerAddress2GarbageCollectionHandle.Add(
		FContainerAddress{InAddress, static_cast<FContainerHelper*>(InContainer)}, GarbageCollectionHandle);

	Address2GarbageCollectionHandle.Add(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2ContainerAddress.Add(GarbageCollectionHandle,
	                                             FContainerAddress{
		                                             InAddress, static_cast<FContainerHelper*>(InContainer)
	                                             });

	MonoObject2GarbageCollectionHandleMap.Add(InMonoObject, GarbageCollectionHandle);

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FContainerReference(GarbageCollectionHandle));
}

bool FContainerRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundContainerAddress = GarbageCollectionHandle2ContainerAddress.Find(InGarbageCollectionHandle))
	{
		ContainerAddress2GarbageCollectionHandle.Remove(*FoundContainerAddress);

		if (FoundContainerAddress->Address != nullptr)
		{
			Address2GarbageCollectionHandle.Remove(FoundContainerAddress->Address);
		}

		if (FoundContainerAddress->ContainerHelper != nullptr)
		{
			delete FoundContainerAddress->ContainerHelper;

			FoundContainerAddress->ContainerHelper = nullptr;
		}

		MonoObject2GarbageCollectionHandleMap.Remove(InGarbageCollectionHandle);

		GarbageCollectionHandle2ContainerAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
