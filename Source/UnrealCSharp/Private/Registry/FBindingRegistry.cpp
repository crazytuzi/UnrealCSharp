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

	BindingAddress2GarbageCollectionHandle.Empty();

	MonoObject2BindingAddress.Empty();
}

MonoObject* FBindingRegistry::GetObject(const void* InObject)
{
	const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find(InObject);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

bool FBindingRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundBindingAddress = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle))
	{
		BindingAddress2GarbageCollectionHandle.Remove(FoundBindingAddress->AddressWrapper->GetValue());

		if (FoundBindingAddress->bNeedFree)
		{
			delete FoundBindingAddress->AddressWrapper;

			FoundBindingAddress->AddressWrapper = nullptr;
		}

		MonoObject2BindingAddress.Remove(InGarbageCollectionHandle);

		GarbageCollectionHandle2BindingAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
