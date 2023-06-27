#include "Registry/FMultiRegistry.h"

FMultiRegistry::FMultiRegistry()
{
	Initialize();
}

FMultiRegistry::~FMultiRegistry()
{
	Deinitialize();
}

void FMultiRegistry::Initialize()
{
}

void FMultiRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2SubclassOfAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2SubclassOfAddress.Empty();

	SubclassOfAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2WeakObjectPtrAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2WeakObjectPtrAddress.Empty();

	WeakObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2LazyObjectPtrAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2LazyObjectPtrAddress.Empty();

	LazyObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2SoftObjectPtrAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2SoftObjectPtrAddress.Empty();

	SoftObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2ScriptInterfaceAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2ScriptInterfaceAddress.Empty();

	ScriptInterfaceAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : GarbageCollectionHandle2SoftClassPtrAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2SoftClassPtrAddress.Empty();

	SoftClassPtrAddress2GarbageCollectionHandle.Empty();
}
