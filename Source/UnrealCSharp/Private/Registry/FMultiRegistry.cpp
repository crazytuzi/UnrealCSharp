#include "Registry/FMultiRegistry.h"
#include "Domain/FDomain.h"

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
	for (auto& [Key, Value] : SubclassOfManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SubclassOfManagedHandle2Address.Empty();

	SubclassOfAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : WeakObjectPtrManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	WeakObjectPtrManagedHandle2Address.Empty();

	WeakObjectPtrAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : LazyObjectPtrManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	LazyObjectPtrManagedHandle2Address.Empty();

	LazyObjectPtrAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : SoftObjectPtrManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SoftObjectPtrManagedHandle2Address.Empty();

	SoftObjectPtrAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : ScriptInterfaceManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	ScriptInterfaceManagedHandle2Address.Empty();

	ScriptInterfaceAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : SoftClassPtrManagedHandle2Address.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			FMemory::Free(Value.Value);

			Value.Value = nullptr;
		}
	}

	SoftClassPtrManagedHandle2Address.Empty();

	SoftClassPtrAddress2ManagedHandle.Empty();
}
