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
	for (auto& [Key, Value] : DelegateGarbageCollectionHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FGarbageCollectionHandle::Free<true>(Key);
	}

	DelegateGarbageCollectionHandle2Helper.Empty();

	DelegateAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : MulticastDelegateGarbageCollectionHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FGarbageCollectionHandle::Free<true>(Key);
	}

	MulticastDelegateGarbageCollectionHandle2Helper.Empty();

	MulticastDelegateAddress2GarbageCollectionHandle.Empty();
}
