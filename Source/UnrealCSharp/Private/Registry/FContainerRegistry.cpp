#include "Registry/FContainerRegistry.h"
#include "Domain/FDomain.h"

FContainerRegistry::FContainerRegistry()
{
	Initialize();
}

FContainerRegistry::~FContainerRegistry()
{
	Deinitialize();
}

void FContainerRegistry::Initialize()
{
}

void FContainerRegistry::Deinitialize()
{
	for (auto& [Key, Value] : ArrayManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	ArrayManagedHandle2Helper.Empty();

	ArrayAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : MapManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	MapManagedHandle2Helper.Empty();

	MapAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : SetManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	SetManagedHandle2Helper.Empty();

	SetAddress2ManagedHandle.Empty();
}
