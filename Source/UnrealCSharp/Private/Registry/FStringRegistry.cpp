#include "Registry/FStringRegistry.h"
#include "Domain/FDomain.h"

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
	for (auto& [Key, Value] : NameManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	NameManagedHandle2Address.Empty();

	NameAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : StringManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	StringManagedHandle2Address.Empty();

	StringAddress2ManagedHandle.Empty();

#if UE_F_UTF8_STR_PROPERTY
	for (auto& [Key, Value] : Utf8StringManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	Utf8StringManagedHandle2Address.Empty();

	Utf8StringAddress2ManagedHandle.Empty();
#endif

#if UE_F_ANSI_STR_PROPERTY
	for (auto& [Key, Value] : AnsiStringManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	AnsiStringManagedHandle2Address.Empty();

	AnsiStringAddress2ManagedHandle.Empty();
#endif

	for (auto& [Key, Value] : TextManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	TextManagedHandle2Address.Empty();

	TextAddress2ManagedHandle.Empty();
}
