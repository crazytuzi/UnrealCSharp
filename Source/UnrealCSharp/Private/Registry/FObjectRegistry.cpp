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
	for (auto& Pair : GarbageCollectionHandle2Object.Get())
	{
		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2Object.Empty();

	MonoObject2Object.Empty();

	Object2GarbageCollectionHandleMap.Empty();
}

void* FObjectRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundObject = GarbageCollectionHandle2Object.Find(InGarbageCollectionHandle);

	return FoundObject != nullptr ? const_cast<UObject*>(FoundObject->Get()) : nullptr;
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject)
{
	const auto FoundObject = MonoObject2Object.Find(InMonoObject);

	return FoundObject != nullptr ? const_cast<UObject*>(FoundObject->Get()) : nullptr;
}

void* FObjectRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct)
{
	if (const auto FoundObject = GarbageCollectionHandle2Object.Find(InGarbageCollectionHandle))
	{
		InStruct = (*FoundObject)->GetClass();

		return const_cast<UObject*>(FoundObject->Get());
	}

	return nullptr;
}

void* FObjectRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundObject = MonoObject2Object.Find(InMonoObject))
	{
		InStruct = (*FoundObject)->GetClass();

		return const_cast<UObject*>(FoundObject->Get());
	}

	return nullptr;
}

MonoObject* FObjectRegistry::GetObject(const UObject* InObject)
{
	const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

UObject* FObjectRegistry::GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	return static_cast<UObject*>(GetAddress(InGarbageCollectionHandle));
}

UObject* FObjectRegistry::GetObject(const MonoObject* InMonoObject)
{
	return static_cast<UObject*>(GetAddress(InMonoObject));
}

FGarbageCollectionHandle FObjectRegistry::GetGarbageCollectionHandle(const UObject* InObject)
{
	const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject);

	return FoundGarbageCollectionHandle != nullptr ? *FoundGarbageCollectionHandle : FGarbageCollectionHandle();
}

bool FObjectRegistry::AddReference(UObject* InObject, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	Object2GarbageCollectionHandleMap.Add(InObject, GarbageCollectionHandle);

	GarbageCollectionHandle2Object.Add(GarbageCollectionHandle, &*InObject);

	MonoObject2Object.Add(InMonoObject, &*InObject);

	return true;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject))
	{
		Object2GarbageCollectionHandleMap.Remove(InObject);

		MonoObject2Object.Remove(*FoundGarbageCollectionHandle);

		GarbageCollectionHandle2Object.Remove(*FoundGarbageCollectionHandle);

		FGarbageCollectionHandle::Free(*FoundGarbageCollectionHandle, false);

		(void)FCSharpEnvironment::GetEnvironment().RemoveReference(*FoundGarbageCollectionHandle);

		return true;
	}

	return false;
}

bool FObjectRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundValue = GarbageCollectionHandle2Object.Find(InGarbageCollectionHandle))
	{
		if (const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(*FoundValue))
		{
			FGarbageCollectionHandle::Free(*FoundGarbageCollectionHandle, false);

			(void)FCSharpEnvironment::GetEnvironment().RemoveReference(*FoundGarbageCollectionHandle);
		}

		MonoObject2Object.Remove(InGarbageCollectionHandle);

		GarbageCollectionHandle2Object.Remove(InGarbageCollectionHandle);

		Object2GarbageCollectionHandleMap.Remove(*FoundValue);

		return true;
	}

	return false;
}
