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
	for (auto& [Key, Value] : ArrayGarbageCollectionHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FGarbageCollectionHandle::Free<true>(Key);
	}

	ArrayGarbageCollectionHandle2Helper.Empty();

	ArrayAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : MapGarbageCollectionHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FGarbageCollectionHandle::Free<true>(Key);
	}

	MapGarbageCollectionHandle2Helper.Empty();

	MapAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : SetGarbageCollectionHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FGarbageCollectionHandle::Free<true>(Key);
	}

	SetGarbageCollectionHandle2Helper.Empty();

	SetAddress2GarbageCollectionHandle.Empty();
}
