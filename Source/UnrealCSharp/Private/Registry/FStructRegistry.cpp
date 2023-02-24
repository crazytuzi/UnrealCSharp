#include "Registry/FStructRegistry.h"
#include "Environment/FCSharpEnvironment.h"

FStructRegistry::FStructRegistry()
{
	Initialize();
}

FStructRegistry::~FStructRegistry()
{
	Deinitialize();
}

void FStructRegistry::Initialize()
{
}

void FStructRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2StructAddress.Get())
	{
		FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(Pair.Key);

		if (Pair.Value.bNeedFree)
		{
			FMemory::Free(Pair.Value.Address);

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2StructAddress.Empty();

	StructAddress2GarbageCollectionHandle.Empty();
}

void* FStructRegistry::GetAddress(const MonoObject* InMonoObject)
{
	const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InMonoObject);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

void* FStructRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InMonoObject))
	{
		InStruct = FoundStructAddress->ScriptStruct;

		return FoundStructAddress->Address;
	}

	return nullptr;
}

MonoObject* FStructRegistry::GetObject(const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find(InStruct);

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FStructRegistry::GetStruct(const MonoObject* InMonoObject)
{
	return GetAddress(InMonoObject);
}

bool FStructRegistry::AddReference(UScriptStruct* InScriptStruct, void* InStruct, MonoObject* InMonoObject,
                                   const bool bNeedFree)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New_WeakRef(
		InMonoObject, false);

	StructAddress2GarbageCollectionHandle.Emplace(InStruct, GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Emplace(GarbageCollectionHandle,
	                                              FStructAddress{InStruct, InScriptStruct, bNeedFree});

	return true;
}

bool FStructRegistry::RemoveReference(const void* InStruct)
{
	if (const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find(InStruct))
	{
		FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(*FoundGarbageCollectionHandle);

		return true;
	}

	return false;
}

bool FStructRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InMonoObject))
	{
		StructAddress2GarbageCollectionHandle.Remove(FoundStructAddress->Address);

		if (FoundStructAddress->bNeedFree)
		{
			FMemory::Free(FoundStructAddress->Address);

			FoundStructAddress->Address = nullptr;
		}

		GarbageCollectionHandle2StructAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}
