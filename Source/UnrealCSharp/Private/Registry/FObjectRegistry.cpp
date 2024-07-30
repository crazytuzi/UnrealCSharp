#include "Registry/FObjectRegistry.h"
#include "CoreMacro/Macro.h"
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
	for (auto& [Key, PLACEHOLDER] : GarbageCollectionHandle2Object.Get())
	{
		FGarbageCollectionHandle::Free<true>(Key);
	}

	GarbageCollectionHandle2Object.Empty();

	Object2GarbageCollectionHandleMap.Empty();
}

void* FObjectRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundObject = GarbageCollectionHandle2Object.Find(InGarbageCollectionHandle);

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

MonoObject* FObjectRegistry::GetObject(const UObject* InObject)
{
	const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

UObject* FObjectRegistry::GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	return static_cast<UObject*>(GetAddress(InGarbageCollectionHandle));
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

	return true;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (const auto FoundGarbageCollectionHandle = Object2GarbageCollectionHandleMap.Find(InObject))
	{
		Object2GarbageCollectionHandleMap.Remove(InObject);

		GarbageCollectionHandle2Object.Remove(*FoundGarbageCollectionHandle);

		FGarbageCollectionHandle::Free<false>(*FoundGarbageCollectionHandle);

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
			if (*FoundGarbageCollectionHandle == InGarbageCollectionHandle)
			{
				FGarbageCollectionHandle::Free<false>(*FoundGarbageCollectionHandle);

				(void)FCSharpEnvironment::GetEnvironment().RemoveReference(*FoundGarbageCollectionHandle);

				Object2GarbageCollectionHandleMap.Remove(*FoundValue);
			}
		}

		GarbageCollectionHandle2Object.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
