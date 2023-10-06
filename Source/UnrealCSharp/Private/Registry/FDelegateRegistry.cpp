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
	for (auto& Pair : GarbageCollectionHandle2DelegateHelperAddress.Get())
	{
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2DelegateHelperAddress.Empty();

	DelegateAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2MulticastDelegateHelperAddress.Get())
	{
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2MulticastDelegateHelperAddress.Empty();

	MulticastDelegateAddress2GarbageCollectionHandle.Empty();
}
