#include "Registry/FMultiRegistry.h"

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
	GarbageCollectionHandle2SubclassOfAddress.Empty();

	SubclassOfAddress2GarbageCollectionHandle.Empty();
}

TSubclassOf<UObject> FMultiRegistry::GetMulti(const MonoObject* InMonoObject)
{
	const auto FoundSubclassOfAddress = GarbageCollectionHandle2SubclassOfAddress.Find(InMonoObject);

	return FoundSubclassOfAddress != nullptr ? FoundSubclassOfAddress->Class : TSubclassOf<UObject>();
}

MonoObject* FMultiRegistry::GetObject(const void* InAddress) const
{
	const auto FoundGarbageCollectionHandle = SubclassOfAddress2GarbageCollectionHandle.Find(InAddress);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

bool FMultiRegistry::AddReference(MonoObject* InMonoObject, const TSubclassOf<UObject>& InClass)
{
	const auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New_WeakRef(
		InMonoObject, true);

	GarbageCollectionHandle2SubclassOfAddress.Emplace(GarbageCollectionHandle,
	                                                  FSubclassOfAddress{nullptr, InClass});

	return true;
}

bool FMultiRegistry::AddReference(void* InAddress, MonoObject* InMonoObject, const TSubclassOf<UObject>& InClass)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New_WeakRef(
		InMonoObject, true);

	SubclassOfAddress2GarbageCollectionHandle.Emplace(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2SubclassOfAddress.Emplace(GarbageCollectionHandle,
	                                                  FSubclassOfAddress{InAddress, InClass});

	return true;
}

bool FMultiRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundSubclassOfAddress = GarbageCollectionHandle2SubclassOfAddress.Find(InMonoObject))
	{
		SubclassOfAddress2GarbageCollectionHandle.Remove(FoundSubclassOfAddress->Address);

		GarbageCollectionHandle2SubclassOfAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

bool FMultiRegistry::RemoveReference(const void* InAddress)
{
	for (const auto& Pair : SubclassOfAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			SubclassOfAddress2GarbageCollectionHandle.Remove(Pair.Key);

			GarbageCollectionHandle2SubclassOfAddress.Remove(Pair.Value);

			return true;
		}
	}

	return false;
}
