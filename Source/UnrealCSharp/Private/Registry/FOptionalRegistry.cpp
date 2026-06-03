#include "Registry/FOptionalRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"

#if UE_F_OPTIONAL_PROPERTY
FOptionalRegistry::FOptionalRegistry()
{
	Initialize();
}

FOptionalRegistry::~FOptionalRegistry()
{
	Deinitialize();
}

void FOptionalRegistry::Initialize()
{
}

void FOptionalRegistry::Deinitialize()
{
	for (auto& [Key, Value] : ManagedHandle2Helper.Get())
	{
		if (Value != nullptr)
		{
			delete Value;

			Value = nullptr;
		}

		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	ManagedHandle2Helper.Empty();

	Address2ManagedHandle.Empty();
}

FOptionalHelper* FOptionalRegistry::GetOptional(const IManagedHandle InManagedHandle)
{
	const auto FoundValue = ManagedHandle2Helper.Find(InManagedHandle);

	return FoundValue != nullptr ? *FoundValue : nullptr;
}

IManagedHandle FOptionalRegistry::GetObject(const FOptionalHelperValueMapping::FAddressType& InAddress)
{
	const auto FoundManagedHandle = Address2ManagedHandle.Find(InAddress);

	return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
}

bool FOptionalRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2Helper.Find(InManagedHandle))
	{
		const auto Address = (*FoundValue)->GetAddress();

		if (const auto FoundManagedHandle = Address2ManagedHandle.Find(Address))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				Address2ManagedHandle.Remove(Address);
			}
		}

		delete *FoundValue;

		ManagedHandle2Helper.Remove(InManagedHandle);

		return true;
	}

	return false;
}
#endif
