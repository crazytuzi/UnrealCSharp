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
	for (auto& Pair : GarbageCollectionHandle2ArrayHelperAddress.Get())
	{
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2ArrayHelperAddress.Empty();

	ArrayHelperAddress2GarbageCollectionHandle.Empty();

	MonoObject2ArrayHelperAddress.Empty();

	ArrayAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2MapHelperAddress.Get())
	{
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2MapHelperAddress.Empty();

	MapHelperAddress2GarbageCollectionHandle.Empty();

	MonoObject2MapHelperAddress.Empty();

	MapAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2SetHelperAddress.Get())
	{
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2SetHelperAddress.Empty();

	SetHelperAddress2GarbageCollectionHandle.Empty();

	MonoObject2SetHelperAddress.Empty();

	SetAddress2GarbageCollectionHandle.Empty();
}
