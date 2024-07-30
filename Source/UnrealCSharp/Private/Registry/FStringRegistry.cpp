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
	for (auto& [Key, Value] : NameGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	NameGarbageCollectionHandle2Address.Empty();

	NameAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : StringGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	StringGarbageCollectionHandle2Address.Empty();

	StringAddress2GarbageCollectionHandle.Empty();

	for (auto& [Key, Value] : TextGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	TextGarbageCollectionHandle2Address.Empty();

	TextAddress2GarbageCollectionHandle.Empty();
}
