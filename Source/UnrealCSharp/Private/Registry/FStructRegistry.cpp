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

		if (Value.bNeedFree)
		{
			if (Value.Value.IsValid())
			{
				if (!(Value.Value->StructFlags & (STRUCT_IsPlainOldData | STRUCT_NoDestructor)))
				{
					Value.Value->DestroyStruct(Value.Address);
				}

				FMemory::Free(Value.Address);
			}

			Value.Address = nullptr;
		}
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
	const auto FoundManagedHandle = StructAddress2ManagedHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	});

	return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
}

void* FStructRegistry::GetStruct(const IManagedHandle InManagedHandle)
{
	return GetAddress(InManagedHandle);
}

IManagedHandle FStructRegistry::GetManagedHandle(UScriptStruct* InScriptStruct, const void* InStruct)
{
	const auto FoundManagedHandle = StructAddress2ManagedHandle.Find({
		InScriptStruct, const_cast<void*>(InStruct)
	});

	return FoundManagedHandle != nullptr ? *FoundManagedHandle : InvalidManagedHandle;
}

bool FStructRegistry::AddReference(const IManagedHandle InOwner, UScriptStruct* InScriptStruct,
                                   const void* InStruct, const IManagedHandle InManagedHandle)
{
	const auto ManagedHandle = FReflectionRegistry::Get().GetClass(InScriptStruct)->NewGCHandle(
		InManagedHandle, true);

	StructAddress2ManagedHandle.Add(
		FStructAddressBase(InScriptStruct, const_cast<void*>(InStruct)), ManagedHandle);

	ManagedHandle2StructAddress.Add(ManagedHandle, {
		                                InScriptStruct,
		                                const_cast<void*>(InStruct),
		                                false
	                                });

	return FCSharpEnvironment::GetEnvironment().
		AddReference(InOwner, new FStructReference(ManagedHandle));
}

bool FStructRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2StructAddress.Find(InManagedHandle))
	{
		if (const auto FoundManagedHandle = StructAddress2ManagedHandle.Find(
			{FoundValue->Value.Get(), FoundValue->Address}))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				FDomain::GCHandle_Free(*FoundManagedHandle);

				(void)FCSharpEnvironment::GetEnvironment().RemoveReference(InManagedHandle);

				StructAddress2ManagedHandle.Remove(
					{FoundValue->Value.Get(), FoundValue->Address});
			}
		}

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

		ManagedHandle2StructAddress.Remove(InManagedHandle);

		return true;
	}

	return false;
}
