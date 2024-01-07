#include "Registry/FStringRegistry.h"

FStringRegistry::FStringRegistry()
{
	Initialize();
}

FStringRegistry::~FStringRegistry()
{
	Deinitialize();
}

void FStringRegistry::Initialize()
{
}

void FStringRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2NameAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	GarbageCollectionHandle2NameAddress.Empty();

	NameAddress2GarbageCollectionHandle.Empty();

	MonoObject2NameAddress.Empty();

	for (auto& Pair : GarbageCollectionHandle2StringAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	GarbageCollectionHandle2StringAddress.Empty();

	StringAddress2GarbageCollectionHandle.Empty();

	MonoObject2StringAddress.Empty();

	for (auto& Pair : GarbageCollectionHandle2TextAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	GarbageCollectionHandle2TextAddress.Empty();

	TextAddress2GarbageCollectionHandle.Empty();

	MonoObject2TextAddress.Empty();
}
