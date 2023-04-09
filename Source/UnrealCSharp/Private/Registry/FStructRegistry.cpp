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
		FGarbageCollectionHandle::Free(Pair.Key);

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

MonoObject* FStructRegistry::GetObject(const void* InOwner, const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InOwner), const_cast<void*>(InStruct)
	});

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FStructRegistry::GetStruct(const MonoObject* InMonoObject)
{
	return GetAddress(InMonoObject);
}

FGarbageCollectionHandle FStructRegistry::GetGarbageCollectionHandle(const void* InOwner, const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InOwner), const_cast<void*>(InStruct)
	});

	return FoundGarbageCollectionHandle != nullptr ? *FoundGarbageCollectionHandle : FGarbageCollectionHandle();
}

bool FStructRegistry::AddReference(UScriptStruct* InScriptStruct, const void* InOwner, const void* InStruct,
                                   MonoObject* InMonoObject,
                                   const bool bNeedFree)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	StructAddress2GarbageCollectionHandle.Emplace(
		FStructAddressBase{const_cast<void*>(InOwner), const_cast<void*>(InStruct)}, GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Emplace(MoveTemp(GarbageCollectionHandle), {
		                                              const_cast<void*>(InOwner), const_cast<void*>(InStruct),
		                                              InScriptStruct, bNeedFree
	                                              });

	return true;
}

bool FStructRegistry::RemoveReference(const void* InOwner, const void* InStruct)
{
	if (const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InOwner), const_cast<void*>(InStruct)
	}))
	{
		FGarbageCollectionHandle::Free(*FoundGarbageCollectionHandle);

		return true;
	}

	return false;
}

bool FStructRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InMonoObject))
	{
		StructAddress2GarbageCollectionHandle.Remove({FoundStructAddress->Owner, FoundStructAddress->Address});

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
