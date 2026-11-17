#include "Registry/FFieldPathRegistry.h"
#include "UObject/Field.h"
#include "Bridge/FTypeBridge.h"
#include "Domain/FDomain.h"

FFieldPathRegistry::FFieldPathRegistry()
{
	Initialize();
}

FFieldPathRegistry::~FFieldPathRegistry()
{
	Deinitialize();
}

void FFieldPathRegistry::Initialize()
{
}

void FFieldPathRegistry::Deinitialize()
{
	for (auto& [Key, Value] : ManagedHandle2Value.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};

		Value.Free();
	}

	ManagedHandle2Value.Empty();

	Address2ManagedHandle.Empty();

	for (auto& [Key, Value] : Field2ManagedHandle)
	{
		FDomain::GCHandle_Free(Value);

		Value = IManagedHandle{};
	}

	Field2ManagedHandle.Empty();

	ManagedHandle2Field.Empty();
}

FFieldPath* FFieldPathRegistry::GetFieldPath(const IManagedHandle InManagedHandle)
{
	const auto FoundValue = ManagedHandle2Value.Find(InManagedHandle);

	return FoundValue != nullptr ? FoundValue->Value : nullptr;
}

IManagedHandle FFieldPathRegistry::GetManagedHandle(const void* InAddress)
{
	if (const auto FoundManagedHandle = Address2ManagedHandle.Find(InAddress))
	{
		if (FDomain::GCHandle_IsAlive(*FoundManagedHandle))
		{
			return *FoundManagedHandle;
		}

		(void)RemoveReference(*FoundManagedHandle);

		Address2ManagedHandle.Remove(InAddress);
	}

	return InvalidManagedHandle;
}

FField* FFieldPathRegistry::GetField(const IManagedHandle InManagedHandle)
{
	const auto FoundField = ManagedHandle2Field.Find(InManagedHandle);

	return FoundField != nullptr ? *FoundField : nullptr;
}

IManagedHandle FFieldPathRegistry::GetFieldObject(FField* InField)
{
	if (InField != nullptr)
	{
		if (const auto FoundManagedHandle = Field2ManagedHandle.Find(InField))
		{
			if (FDomain::GCHandle_IsAlive(*FoundManagedHandle))
			{
				return *FoundManagedHandle;
			}

			ManagedHandle2Field.Remove(*FoundManagedHandle);
		}

		if (const auto Class = FTypeBridge::GetClass(InField->GetClass()))
		{
			if (const auto Object = Class->NewObject(true); IManagedHandleIsValid(Object))
			{
				Field2ManagedHandle.Add(InField, Object);

				ManagedHandle2Field.Add(Object, InField);

				return Object;
			}
		}
	}

	return InvalidManagedHandle;
}

bool FFieldPathRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2Value.Find(InManagedHandle))
	{
		if (const auto FoundManagedHandle = Address2ManagedHandle.Find(FoundValue->Value))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				Address2ManagedHandle.Remove(FoundValue->Value);
			}
		}

		FoundValue->Free();

		ManagedHandle2Value.Remove(InManagedHandle);

		FDomain::GCHandle_Free(InManagedHandle);

		return true;
	}

	return false;
}
