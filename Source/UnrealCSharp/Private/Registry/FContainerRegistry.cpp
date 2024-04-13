#include "Registry/FContainerRegistry.h"

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
	for (auto& Pair : ArrayGarbageCollectionHandle2Helper.Get())
	{
		if (Pair.Value != nullptr)
		{
			delete Pair.Value;

			Pair.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	ArrayGarbageCollectionHandle2Helper.Empty();

	ArrayAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : MapGarbageCollectionHandle2Helper.Get())
	{
		if (Pair.Value != nullptr)
		{
			delete Pair.Value;

			Pair.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	MapGarbageCollectionHandle2Helper.Empty();

	MapAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : SetGarbageCollectionHandle2Helper.Get())
	{
		if (Pair.Value != nullptr)
		{
			delete Pair.Value;

			Pair.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	SetGarbageCollectionHandle2Helper.Empty();

	SetAddress2GarbageCollectionHandle.Empty();
}
