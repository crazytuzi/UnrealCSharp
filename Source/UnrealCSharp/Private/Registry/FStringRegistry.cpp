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

#if UE_F_UTF8_STR_PROPERTY
	for (auto& [Key, Value] : Utf8StringGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	Utf8StringGarbageCollectionHandle2Address.Empty();

	Utf8StringAddress2GarbageCollectionHandle.Empty();
#endif

#if UE_F_ANSI_STR_PROPERTY
	for (auto& [Key, Value] : AnsiStringGarbageCollectionHandle2Address.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	AnsiStringGarbageCollectionHandle2Address.Empty();

	AnsiStringAddress2GarbageCollectionHandle.Empty();
#endif

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
