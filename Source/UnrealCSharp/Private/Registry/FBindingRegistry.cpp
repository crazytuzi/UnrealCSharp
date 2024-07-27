#include "Registry/FBindingRegistry.h"

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
	for (auto& [Key, Value] : GarbageCollectionHandle2BindingAddress.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);

		if (Value.bNeedFree)
		{
			delete Value.AddressWrapper;

			Value.AddressWrapper = nullptr;
		}
	}

	GarbageCollectionHandle2BindingAddress.Empty();

	BindingAddress2GarbageCollectionHandle.Empty();
}

MonoObject* FBindingRegistry::GetObject(const FBindingValueMapping::FAddressType InAddress)
{
	const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

bool FBindingRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundValue = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle))
	{
		if (const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find(
			FoundValue->AddressWrapper->Value))
		{
			if (*FoundGarbageCollectionHandle == InGarbageCollectionHandle)
			{
				BindingAddress2GarbageCollectionHandle.Remove(FoundValue->AddressWrapper->Value);
			}
		}

		if (FoundValue->bNeedFree)
		{
			delete FoundValue->AddressWrapper;

			FoundValue->AddressWrapper = nullptr;
		}

		GarbageCollectionHandle2BindingAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
