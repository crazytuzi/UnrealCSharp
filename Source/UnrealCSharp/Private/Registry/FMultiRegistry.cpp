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
	for (auto& Pair : SubclassOfGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	SubclassOfGarbageCollectionHandle2Address.Empty();

	SubclassOfAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : WeakObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	WeakObjectPtrGarbageCollectionHandle2Address.Empty();

	WeakObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : LazyObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	LazyObjectPtrGarbageCollectionHandle2Address.Empty();

	LazyObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : SoftObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	SoftObjectPtrGarbageCollectionHandle2Address.Empty();

	SoftObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : ScriptInterfaceGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	ScriptInterfaceGarbageCollectionHandle2Address.Empty();

	ScriptInterfaceAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : SoftClassPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	SoftClassPtrGarbageCollectionHandle2Address.Empty();

	SoftClassPtrAddress2GarbageCollectionHandle.Empty();
}
