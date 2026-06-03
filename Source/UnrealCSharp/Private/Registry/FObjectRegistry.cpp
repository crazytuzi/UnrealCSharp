#include "Registry/FObjectRegistry.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"
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
	for (auto& [Key, _] : ManagedHandle2Object.Get())
	{
		FDomain::GCHandle_Free(Key);

		Key = IManagedHandle{};
	}

	ManagedHandle2Object.Empty();

	Object2ManagedHandle.Empty();
}

void* FObjectRegistry::GetAddress(const IManagedHandle InManagedHandle)
{
	const auto FoundObject = ManagedHandle2Object.Find(InManagedHandle);

	return FoundObject != nullptr ? const_cast<UObject*>(FoundObject->Get()) : nullptr;
}

void* FObjectRegistry::GetAddress(const IManagedHandle InManagedHandle, UStruct*& InStruct)
{
	if (const auto FoundObject = ManagedHandle2Object.Find(InManagedHandle))
	{
		InStruct = (*FoundObject)->GetClass();

		return const_cast<UObject*>(FoundObject->Get());
	}

	return nullptr;
}

IManagedHandle FObjectRegistry::GetObject(const UObject* InObject)
{
	const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject);

	return FoundManagedHandle != nullptr ? FDomain::GCHandle_Get_Target(*FoundManagedHandle) : InvalidManagedHandle;
}

UObject* FObjectRegistry::GetObject(const IManagedHandle InManagedHandle)
{
	return static_cast<UObject*>(GetAddress(InManagedHandle));
}

IManagedHandle FObjectRegistry::GetManagedHandle(const UObject* InObject)
{
	const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject);

	return FoundManagedHandle != nullptr ? *FoundManagedHandle : InvalidManagedHandle;
}

bool FObjectRegistry::AddReference(const FClassReflection* InClass, UObject* InObject,
                                   const IManagedHandle InManagedHandle)
{
	const auto ManagedHandle = InClass->NewGCHandle(InManagedHandle, true);

	Object2ManagedHandle.Add(InObject, ManagedHandle);

	ManagedHandle2Object.Add(ManagedHandle, &*InObject);

	return true;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject))
	{
		Object2ManagedHandle.Remove(InObject);

		ManagedHandle2Object.Remove(*FoundManagedHandle);

		FDomain::GCHandle_Free(*FoundManagedHandle);

		(void)FCSharpEnvironment::GetEnvironment().RemoveReference(*FoundManagedHandle);

		return true;
	}

	return false;
}

bool FObjectRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2Object.Find(InManagedHandle))
	{
		if (const auto FoundManagedHandle = Object2ManagedHandle.Find(*FoundValue))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				FDomain::GCHandle_Free(*FoundManagedHandle);

				(void)FCSharpEnvironment::GetEnvironment().RemoveReference(*FoundManagedHandle);

				Object2ManagedHandle.Remove(*FoundValue);
			}
		}

		ManagedHandle2Object.Remove(InManagedHandle);

		return true;
	}

	return false;
}
