#include "Registry/FObjectRegistry.h"
#include "Environment/FCSharpEnvironment.h"

FObjectRegistry::FObjectRegistry()
{
	Initialize();
}

FObjectRegistry::~FObjectRegistry()
{
	Deinitialize();
}

void FObjectRegistry::Initialize()
{
}

void FObjectRegistry::Deinitialize()
{
	for (const auto& Pair : GarbageCollectionHandle2Object.Get())
	{
		FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(Pair.Key);
	}

	GarbageCollectionHandle2Object.Empty();

	Object2GarbageCollectionHandleMap.Empty();
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject)
{
	const auto FoundObject = GarbageCollectionHandle2Object.Find(InMonoObject);

	return FoundObject != nullptr ? *FoundObject : nullptr;
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundObject = GarbageCollectionHandle2Object.Find(InMonoObject))
	{
		InStruct = (*FoundObject)->GetClass();

		return *FoundObject;
	}

	return nullptr;
}

MonoObject* FObjectRegistry::GetObject(const UObject* InObject)
{
	const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

UObject* FObjectRegistry::GetObject(const MonoObject* InMonoObject)
{
	return static_cast<UObject*>(GetAddress(InMonoObject));
}

bool FObjectRegistry::AddReference(UObject* InObject, MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New(InMonoObject, false);

	Object2GarbageCollectionHandleMap.Emplace(InObject, GarbageCollectionHandle);

	GarbageCollectionHandle2Object.Emplace(GarbageCollectionHandle, &*InObject);

	return true;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject))
	{
		Object2GarbageCollectionHandleMap.Remove(InObject);

		GarbageCollectionHandle2Object.Remove(*FoundGarbageCollectionHandle);

		FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(*FoundGarbageCollectionHandle);

		return true;
	}

	return false;
}

bool FObjectRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundObject = GarbageCollectionHandle2Object.Find(InMonoObject))
	{
		if (const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(*FoundObject))
		{
			FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(*FoundGarbageCollectionHandle);
		}

		GarbageCollectionHandle2Object.Remove(InMonoObject);

		Object2GarbageCollectionHandleMap.Remove(*FoundObject);

		return true;
	}

	return false;
}
