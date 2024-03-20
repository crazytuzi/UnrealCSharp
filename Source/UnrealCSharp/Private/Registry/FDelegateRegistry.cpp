#include "Registry/FDelegateRegistry.h"

FDelegateRegistry::FDelegateRegistry()
{
	Initialize();
}

FDelegateRegistry::~FDelegateRegistry()
{
	Deinitialize();
}

void FDelegateRegistry::Initialize()
{
}

void FDelegateRegistry::Deinitialize()
{
	for (auto& Pair : DelegateGarbageCollectionHandle2Helper.Get())
	{
		if (Pair.Value != nullptr)
		{
			delete Pair.Value;

			Pair.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	DelegateGarbageCollectionHandle2Helper.Empty();

	DelegateAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : MulticastDelegateGarbageCollectionHandle2Helper.Get())
	{
		if (Pair.Value != nullptr)
		{
			delete Pair.Value;

			Pair.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	MulticastDelegateGarbageCollectionHandle2Helper.Empty();

	MulticastDelegateAddress2GarbageCollectionHandle.Empty();
}
