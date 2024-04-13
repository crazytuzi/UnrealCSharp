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
	for (auto& Pair : NameGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	NameGarbageCollectionHandle2Address.Empty();

	NameAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : StringGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	StringGarbageCollectionHandle2Address.Empty();

	StringAddress2GarbageCollectionHandle.Empty();

	for (auto& Pair : TextGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Value);

			Pair.Value.Value = nullptr;
		}
	}

	TextGarbageCollectionHandle2Address.Empty();

	TextAddress2GarbageCollectionHandle.Empty();
}
