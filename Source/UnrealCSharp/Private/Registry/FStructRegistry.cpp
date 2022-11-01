#include "Registry/FStructRegistry.h"

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
	for (auto& MonoObject2StructAddress : MonoObject2StructAddressMap)
	{
		FMemory::Free(MonoObject2StructAddress.Value.Address);

		MonoObject2StructAddress.Value.Address = nullptr;
	}

	StructAddress2MonoObjectMap.Empty();

	MonoObject2StructAddressMap.Empty();
}

MonoObject* FStructRegistry::GetObject(const void* InStruct)
{
	const auto FoundMonoObject = StructAddress2MonoObjectMap.Find(InStruct);

	return FoundMonoObject != nullptr ? *FoundMonoObject : nullptr;
}

void* FStructRegistry::GetStruct(const MonoObject* InMonoObject)
{
	const auto FoundStructAddress = MonoObject2StructAddressMap.Find(InMonoObject);

	return FoundStructAddress != nullptr ? (*FoundStructAddress).Address : nullptr;
}

void* FStructRegistry::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct)
{
	if (const auto FoundStructAddress = MonoObject2StructAddressMap.Find(InMonoObject))
	{
		InStruct = FoundStructAddress->ScriptStruct;

		return FoundStructAddress->Address;
	}

	return nullptr;
}

bool FStructRegistry::AddReference(UScriptStruct* InScriptStruct, void* InStruct, MonoObject* InMonoObject)
{
	StructAddress2MonoObjectMap.Emplace(InStruct, InMonoObject);

	MonoObject2StructAddressMap.Emplace(InMonoObject, FStructAddress{InStruct, InScriptStruct});

	return true;
}

bool FStructRegistry::RemoveReference(const void* InStruct)
{
	if (const auto FoundMonoObject = StructAddress2MonoObjectMap.Find(InStruct))
	{
		if (const auto FoundStructAddress = MonoObject2StructAddressMap.Find(*FoundMonoObject))
		{
			FMemory::Free(FoundStructAddress->Address);

			FoundStructAddress->Address = nullptr;
		}

		StructAddress2MonoObjectMap.Remove(InStruct);

		MonoObject2StructAddressMap.Remove(*FoundMonoObject);
	}

	return true;
}

bool FStructRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto FoundStructAddress = MonoObject2StructAddressMap.Find(InMonoObject))
	{
		FMemory::Free(FoundStructAddress->Address);

		FoundStructAddress->Address = nullptr;

		MonoObject2StructAddressMap.Remove(InMonoObject);

		StructAddress2MonoObjectMap.Remove(FoundStructAddress);
	}

	return true;
}
