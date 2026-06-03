#include "Registry/FBindingRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"

FBindingRegistry::FBindingRegistry()
{
	Initialize();
}

FBindingRegistry::~FBindingRegistry()
{
	Deinitialize();
}

void FBindingRegistry::Initialize()
{
}

void FBindingRegistry::Deinitialize()
{
	for (auto& [Key, Value] : ManagedHandle2BindingAddress.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		if (Value.bNeedFree)
		{
			delete Value.AddressWrapper;

			Value.AddressWrapper = nullptr;
		}
	}

	ManagedHandle2BindingAddress.Empty();

	BindingAddress2ManagedHandle.Empty();
}

IManagedHandle FBindingRegistry::GetObject(const FBindingValueMapping::FAddressType InAddress)
{
	const auto FoundManagedHandle = BindingAddress2ManagedHandle.Find(InAddress);

	if (FoundManagedHandle == nullptr)
	{
		return InvalidManagedHandle;
	}

	return FDomain::GCHandle_Get_Target(*FoundManagedHandle);
}

bool FBindingRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2BindingAddress.Find(InManagedHandle))
	{
		if (const auto FoundManagedHandle = BindingAddress2ManagedHandle.Find(
			FoundValue->AddressWrapper->Value))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				BindingAddress2ManagedHandle.Remove(FoundValue->AddressWrapper->Value);
			}
		}

		if (FoundValue->bNeedFree)
		{
			delete FoundValue->AddressWrapper;

			FoundValue->AddressWrapper = nullptr;
		}

		ManagedHandle2BindingAddress.Remove(InManagedHandle);

		return true;
	}

	return false;
}
