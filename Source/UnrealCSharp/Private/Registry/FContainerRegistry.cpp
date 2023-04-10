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
}

MonoObject* FContainerRegistry::GetObject(const void* InAddress)
{
	for (const auto& Pair : ContainerAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			return Pair.Value;
		}
	}

	return nullptr;
}

bool FContainerRegistry::AddReference(void* InContainer, MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	ContainerAddress2GarbageCollectionHandle.Emplace(
		FContainerAddress{nullptr, static_cast<FContainerHelper*>(InContainer)}, GarbageCollectionHandle);

	GarbageCollectionHandle2ContainerAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                 FContainerAddress{
		                                                 nullptr, static_cast<FContainerHelper*>(InContainer)
	                                                 });

	return true;
}

bool FContainerRegistry::AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
                                      MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, false);

	ContainerAddress2GarbageCollectionHandle.Emplace(
		FContainerAddress{InAddress, static_cast<FContainerHelper*>(InContainer)}, GarbageCollectionHandle);

	GarbageCollectionHandle2ContainerAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                 FContainerAddress{
		                                                 InAddress, static_cast<FContainerHelper*>(InContainer)
	                                                 });

	return FCSharpEnvironment::GetEnvironment()->
		AddReference(InOwner, new FContainerReference(GarbageCollectionHandle));
}

bool FContainerRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto& FoundContainerAddress = GarbageCollectionHandle2ContainerAddress.Find(InMonoObject))
	{
		ContainerAddress2GarbageCollectionHandle.Remove(*FoundContainerAddress);

		if (FoundContainerAddress->ContainerHelper != nullptr)
		{
			delete FoundContainerAddress->ContainerHelper;

			FoundContainerAddress->ContainerHelper = nullptr;
		}

		GarbageCollectionHandle2ContainerAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

bool FContainerRegistry::RemoveReference(const void* InAddress)
{
	for (auto& Pair : ContainerAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			ContainerAddress2GarbageCollectionHandle.Remove(Pair.Key);

			if (Pair.Key.ContainerHelper != nullptr)
			{
				delete Pair.Key.ContainerHelper;

				Pair.Key.ContainerHelper = nullptr;
			}

			GarbageCollectionHandle2ContainerAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}
