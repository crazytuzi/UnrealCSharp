#include "Registry/FStructRegistry.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reference/FStructReference.h"

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
			if (Pair.Value.Value.IsValid())
			{
				if (!(Pair.Value.Value->StructFlags & (STRUCT_IsPlainOldData | STRUCT_NoDestructor)))
				{
					Pair.Value.Value->DestroyStruct(Pair.Value.Address);
				}

				FMemory::Free(Pair.Value.Address);
			}

			Pair.Value.Address = nullptr;
		}
	}

	GarbageCollectionHandle2StructAddress.Empty();

	StructAddress2GarbageCollectionHandle.Empty();

	MonoObject2StructAddress.Empty();
}

void* FStructRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InGarbageCollectionHandle);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

void* FStructRegistry::GetAddress(const MonoObject* InMonoObject)
{
	const auto FoundStructAddress = MonoObject2StructAddress.Find(InMonoObject);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

void* FStructRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct)
{
	if (const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InGarbageCollectionHandle))
	{
		InStruct = FoundStructAddress->Value.Get();

		return FoundStructAddress->Address;
	}

	return nullptr;
}

void* FStructRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundStructAddress = MonoObject2StructAddress.Find(InMonoObject))
	{
		InStruct = FoundStructAddress->Value.Get();

		return FoundStructAddress->Address;
	}

	return nullptr;
}

MonoObject* FStructRegistry::GetObject(UScriptStruct* InScriptStruct, const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InStruct), InScriptStruct
	});

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FStructRegistry::GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	return GetAddress(InGarbageCollectionHandle);
}

void* FStructRegistry::GetStruct(const MonoObject* InMonoObject)
{
	return GetAddress(InMonoObject);
}

FGarbageCollectionHandle FStructRegistry::GetGarbageCollectionHandle(UScriptStruct* InScriptStruct,
                                                                     const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		const_cast<void*>(InStruct), InScriptStruct
	});

	return FoundGarbageCollectionHandle != nullptr ? *FoundGarbageCollectionHandle : FGarbageCollectionHandle();
}

bool FStructRegistry::AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject,
                                   bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	StructAddress2GarbageCollectionHandle.Add(
		FStructAddressBase{const_cast<void*>(InStruct), InScriptStruct}, GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          const_cast<void*>(InStruct),
		                                          InScriptStruct,
		                                          bNeedFree
	                                          });

	MonoObject2StructAddress.Add(InMonoObject, {
		                             const_cast<void*>(InStruct),
		                             InScriptStruct,
		                             bNeedFree
	                             });

	return true;
}

bool FStructRegistry::AddReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
                                   const void* InStruct, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	StructAddress2GarbageCollectionHandle.Add(
		FStructAddressBase{const_cast<void*>(InStruct), InScriptStruct}, GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          const_cast<void*>(InStruct),
		                                          InScriptStruct,
		                                          false
	                                          });

	MonoObject2StructAddress.Add(InMonoObject, {
		                             const_cast<void*>(InStruct),
		                             InScriptStruct,
		                             false
	                             });

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FStructReference(GarbageCollectionHandle));
}

bool FStructRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InGarbageCollectionHandle))
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveReference(InGarbageCollectionHandle);

		StructAddress2GarbageCollectionHandle.Remove({
			FoundStructAddress->Address, FoundStructAddress->Value.Get()
		});

		if (FoundStructAddress->bNeedFree)
		{
			if (FoundStructAddress->Value.IsValid())
			{
				if (!(FoundStructAddress->Value->StructFlags & (STRUCT_IsPlainOldData | STRUCT_NoDestructor)))
				{
					FoundStructAddress->Value->DestroyStruct(FoundStructAddress->Address);
				}

				FMemory::Free(FoundStructAddress->Address);
			}

			FoundStructAddress->Address = nullptr;
		}

		MonoObject2StructAddress.Remove(InGarbageCollectionHandle);

		GarbageCollectionHandle2StructAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
