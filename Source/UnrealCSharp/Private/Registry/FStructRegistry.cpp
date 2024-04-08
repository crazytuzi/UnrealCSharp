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
}

void* FStructRegistry::GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	const auto FoundStructAddress = GarbageCollectionHandle2StructAddress.Find(InGarbageCollectionHandle);

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

MonoObject* FStructRegistry::GetObject(UScriptStruct* InScriptStruct, const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	});

	return FoundGarbageCollectionHandle != nullptr ? static_cast<MonoObject*>(*FoundGarbageCollectionHandle) : nullptr;
}

void* FStructRegistry::GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	return GetAddress(InGarbageCollectionHandle);
}

FGarbageCollectionHandle FStructRegistry::GetGarbageCollectionHandle(UScriptStruct* InScriptStruct,
                                                                     const void* InStruct)
{
	const auto FoundGarbageCollectionHandle = StructAddress2GarbageCollectionHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	});

	return FoundGarbageCollectionHandle != nullptr ? *FoundGarbageCollectionHandle : FGarbageCollectionHandle();
}

bool FStructRegistry::AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject,
                                   bool bNeedFree)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          InScriptStruct,
		                                          const_cast<void*>(InStruct),
		                                          bNeedFree
	                                          });

	return true;
}

bool FStructRegistry::AddReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
                                   const void* InStruct, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	StructAddress2GarbageCollectionHandle.Add(
		FStructAddressBase(InScriptStruct, const_cast<void*>(InStruct)), GarbageCollectionHandle);

	GarbageCollectionHandle2StructAddress.Add(GarbageCollectionHandle, {
		                                          InScriptStruct,
		                                          const_cast<void*>(InStruct),
		                                          false
	                                          });

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FStructReference(GarbageCollectionHandle));
}

bool FStructRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto FoundValue = GarbageCollectionHandle2StructAddress.Find(InGarbageCollectionHandle))
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveReference(InGarbageCollectionHandle);

		StructAddress2GarbageCollectionHandle.Remove({
			FoundValue->Value.Get(), FoundValue->Address
		});

		if (FoundValue->bNeedFree)
		{
			if (FoundValue->Value.IsValid())
			{
				if (!(FoundValue->Value->StructFlags & (STRUCT_IsPlainOldData | STRUCT_NoDestructor)))
				{
					FoundValue->Value->DestroyStruct(FoundValue->Address);
				}

				FMemory::Free(FoundValue->Address);
			}

			FoundValue->Address = nullptr;
		}

		GarbageCollectionHandle2StructAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
