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
		if (const auto Object = FoundObject->Get())
		{
			InStruct = Object->GetClass();

			return const_cast<UObject*>(Object);
		}
	}

	return nullptr;
}

IManagedHandle FObjectRegistry::GetObject(const UObject* InObject)
{
	if (InObject != nullptr)
	{
		if (const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject))
		{
			return *FoundManagedHandle;
		}
	}

	return InvalidManagedHandle;
}

UObject* FObjectRegistry::GetObject(const IManagedHandle InManagedHandle)
{
	return static_cast<UObject*>(GetAddress(InManagedHandle));
}

IManagedHandle FObjectRegistry::GetManagedHandle(const UObject* InObject)
{
	if (InObject != nullptr)
	{
		if (const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject))
		{
			return *FoundManagedHandle;
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FObjectRegistry::AddReference(UObject* InObject, const IManagedHandle InManagedHandle)
{
	if (const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject))
	{
		const auto ManagedHandle = *FoundManagedHandle;

		if (ManagedHandle != InManagedHandle)
		{
			FDomain::GCHandle_Free(InManagedHandle);
		}

		return ManagedHandle;
	}

	Object2ManagedHandle.Add(InObject, InManagedHandle);

	ManagedHandle2Object.Add(InManagedHandle, std::as_const(InObject));

	return InManagedHandle;
}

bool FObjectRegistry::RemoveReference(const UObject* InObject)
{
	if (InObject != nullptr)
	{
		if (const auto FoundManagedHandle = Object2ManagedHandle.Find(InObject))
		{
			const auto ManagedHandle = *FoundManagedHandle;

			Object2ManagedHandle.Remove(InObject);

			ManagedHandle2Object.Remove(ManagedHandle);

			FDomain::GCHandle_Free(ManagedHandle);

			(void)FCSharpEnvironment::GetEnvironment().RemoveReference(ManagedHandle);

			return true;
		}
	}

	return false;
}

bool FObjectRegistry::RemoveReference(const IManagedHandle InManagedHandle)
{
	if (const auto FoundValue = ManagedHandle2Object.Find(InManagedHandle))
	{
		const auto Object = FoundValue->Get();

		if (const auto FoundManagedHandle = Object2ManagedHandle.Find(Object))
		{
			if (*FoundManagedHandle == InManagedHandle)
			{
				Object2ManagedHandle.Remove(Object);

				FDomain::GCHandle_Free(InManagedHandle);

				(void)FCSharpEnvironment::GetEnvironment().RemoveReference(InManagedHandle);
			}
		}

		ManagedHandle2Object.Remove(InManagedHandle);

		return true;
	}

	return false;
}
