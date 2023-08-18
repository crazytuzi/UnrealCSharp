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
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2BindingAddress.Empty();

	BindingAddress2GarbageCollectionHandle.Empty();
}

MonoObject* FBindingRegistry::GetObject(const void* InObject)
{
	const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InObject)
	});

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FBindingRegistry::GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundStructAddress = GarbageCollectionHandle2BindingAddress.Find(InGarbageCollectionHandle);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

bool FBindingRegistry::AddReference(const void* InObject, MonoObject* InMonoObject, bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Add(FBindingAddress{const_cast<void*>(InObject), bNeedFree},
	                                           GarbageCollectionHandle);

	GarbageCollectionHandle2BindingAddress.Add(GarbageCollectionHandle,
	                                           {const_cast<void*>(InObject), bNeedFree});

	return true;
}
