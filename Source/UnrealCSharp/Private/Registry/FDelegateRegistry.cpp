#include "Registry/FDelegateRegistry.h"
#include "Domain/FDomain.h"

FDelegateRegistry::FDelegateRegistry()
{
	Initialize();
}

FDelegateRegistry::~FDelegateRegistry()
{
	Deinitialize();
}

void FDelegateRegistry::Initialize()
{
}

void FDelegateRegistry::Deinitialize()
{
	for (auto& [Key, Value] : DelegateManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	DelegateManagedHandle2Helper.Empty();

	DelegateAddress2ManagedHandle.Empty();

	for (auto& [Key, Value] : MulticastDelegateManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	MulticastDelegateManagedHandle2Helper.Empty();

	MulticastDelegateAddress2ManagedHandle.Empty();
}
