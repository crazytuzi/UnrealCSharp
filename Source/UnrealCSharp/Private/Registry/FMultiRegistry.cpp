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
	for (auto& [Key, Value] : SubclassOfGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SubclassOfGarbageCollectionHandle2Address.Empty();

	SubclassOfAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : WeakObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	WeakObjectPtrGarbageCollectionHandle2Address.Empty();

	WeakObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : LazyObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	LazyObjectPtrGarbageCollectionHandle2Address.Empty();

	LazyObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : SoftObjectPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SoftObjectPtrGarbageCollectionHandle2Address.Empty();

	SoftObjectPtrAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : ScriptInterfaceGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	ScriptInterfaceGarbageCollectionHandle2Address.Empty();

	ScriptInterfaceAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : SoftClassPtrGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SoftClassPtrGarbageCollectionHandle2Address.Empty();

	SoftClassPtrAddress2GarbageCollectionHandle.Empty();
}
