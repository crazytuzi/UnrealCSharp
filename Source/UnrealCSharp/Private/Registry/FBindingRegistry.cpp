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
	for (auto& Pair : GarbageCollectionHandle2BindingAddress.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			delete Pair.Value.AddressWrapper;

			Pair.Value.AddressWrapper = nullptr;
		}
	}

	GarbageCollectionHandle2BindingAddress.Empty();

	MonoObject2BindingAddress.Empty();

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
		BindingAddress2GarbageCollectionHandle.Remove(FoundValue->AddressWrapper->GetValue());

		if (FoundValue->bNeedFree)
		{
			delete FoundValue->AddressWrapper;

			FoundValue->AddressWrapper = nullptr;
		}

		MonoObject2BindingAddress.Remove(InGarbageCollectionHandle);

		GarbageCollectionHandle2BindingAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
