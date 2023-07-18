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

void* FBindingRegistry::GetObject(const MonoObject* InMonoObject)
{
	const auto FoundStructAddress = GarbageCollectionHandle2BindingAddress.Find(InMonoObject);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

bool FBindingRegistry::AddReference(const void* InObject, MonoObject* InMonoObject, bool bNeedFree)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	BindingAddress2GarbageCollectionHandle.Emplace(FBindingAddress{const_cast<void*>(InObject), bNeedFree},
	                                               GarbageCollectionHandle);

	GarbageCollectionHandle2BindingAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                               {const_cast<void*>(InObject), bNeedFree});

	return true;
}

bool FBindingRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundObject = GarbageCollectionHandle2BindingAddress.Find(InMonoObject))
	{
		if (const auto FoundGarbageCollectionHandle = BindingAddress2GarbageCollectionHandle.Find(*FoundObject))
		{
			FGarbageCollectionHandle::Free(*FoundGarbageCollectionHandle, false);
		}

		GarbageCollectionHandle2BindingAddress.Remove(InMonoObject);

		BindingAddress2GarbageCollectionHandle.Remove(*FoundObject);

		return true;
	}

	return false;
}
