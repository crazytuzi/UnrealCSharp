#include "Registry/FStructRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"
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
	for (auto& [Key, Value] : ManagedHandle2StructAddress.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		Value.Free();
	}

	ManagedHandle2StructAddress.Empty();

	StructAddress2ManagedHandle.Empty();
}

void* FStructRegistry::GetAddress(const IManagedHandle InManagedHandle)
{
	const auto FoundStructAddress = ManagedHandle2StructAddress.Find(InManagedHandle);

	return FoundStructAddress != nullptr ? FoundStructAddress->Address : nullptr;
}

void* FStructRegistry::GetAddress(const IManagedHandle InManagedHandle, UStruct*& InStruct)
{
	if (const auto FoundStructAddress = ManagedHandle2StructAddress.Find(InManagedHandle))
	{
		InStruct = FoundStructAddress->Value.Get();

		return FoundStructAddress->Address;
	}

	return nullptr;
}

IManagedHandle FStructRegistry::GetObject(UScriptStruct* InScriptStruct, const void* InStruct)
{
	if (const auto FoundManagedHandle = StructAddress2ManagedHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	}))
	{
		if (FDomain::GCHandle_IsAlive(*FoundManagedHandle))
		{
			return *FoundManagedHandle;
		}

		(void)RemoveReference(*FoundManagedHandle);

		StructAddress2ManagedHandle.Remove({InScriptStruct, const_cast<void*>(InStruct)});
	}

	return InvalidManagedHandle;
}

void* FStructRegistry::GetStruct(const IManagedHandle InManagedHandle)
{
	return GetAddress(InManagedHandle);
}

IManagedHandle FStructRegistry::GetManagedHandle(UScriptStruct* InScriptStruct, const void* InStruct)
{
	if (const auto FoundManagedHandle = StructAddress2ManagedHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	}))
	{
		if (FDomain::GCHandle_IsAlive(*FoundManagedHandle))
		{
			return *FoundManagedHandle;
		}

		(void)RemoveReference(*FoundManagedHandle);

		StructAddress2ManagedHandle.Remove({InScriptStruct, const_cast<void*>(InStruct)});
	}

	return InvalidManagedHandle;
}

bool FStructRegistry::AddReference(const IManagedHandle InOwner, UScriptStruct* InScriptStruct,
                                   const void* InStruct, const IManagedHandle InManagedHandle)
{
	StructAddress2ManagedHandle.Add(
		FStructAddressBase(InScriptStruct, const_cast<void*>(InStruct)), InManagedHandle);

	ManagedHandle2StructAddress.Add(InManagedHandle, {
		                                InScriptStruct,
		                                const_cast<void*>(InStruct),
		                                false
	                                });

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FStructReference(InManagedHandle));
}

bool FStructRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2StructAddress.Find(InManagedHandle))
	{
		FDomain::GCHandle_Free(InManagedHandle);

		if (const auto FoundManagedHandle = StructAddress2ManagedHandle.Find({
			FoundValue->Value.Get(), FoundValue->Address
		}))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				StructAddress2ManagedHandle.Remove({FoundValue->Value.Get(), FoundValue->Address});
			}
		}

		FoundValue->Free();

		ManagedHandle2StructAddress.Remove(InManagedHandle);

		(void)FCSharpEnvironment::GetEnvironment().RemoveReference(InManagedHandle);

		return true;
	}

	return false;
}
