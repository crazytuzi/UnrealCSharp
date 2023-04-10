#include "Registry/FDelegateRegistry.h"
#include "Reference/FDelegateReference.h"
#include "Environment/FCSharpEnvironment.h"

FDelegateRegistry::FDelegateRegistry()
{
	Initialize();
}

FDelegateRegistry::~FDelegateRegistry()
{
	Deinitialize();
}

void FDelegateRegistry::Initialize()
{
}

void FDelegateRegistry::Deinitialize()
{
	for (auto& Pair : GarbageCollectionHandle2DelegateAddress.Get())
	{
		if (Pair.Value.DelegateBaseHelper != nullptr)
		{
			delete Pair.Value.DelegateBaseHelper;

			Pair.Value.DelegateBaseHelper = nullptr;
		}

		FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(Pair.Key);
	}

	GarbageCollectionHandle2DelegateAddress.Empty();

	DelegateAddress2GarbageCollectionHandle.Empty();
}

MonoObject* FDelegateRegistry::GetObject(const void* InAddress)
{
	for (const auto& Pair : DelegateAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			return Pair.Value;
		}
	}

	return nullptr;
}

bool FDelegateRegistry::AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New_WeakRef(
		InMonoObject, false);

	DelegateAddress2GarbageCollectionHandle.Emplace(
		FDelegateAddress{InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)}, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(GarbageCollectionHandle,
	                                                FDelegateAddress{
		                                                InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                                });

	return true;
}

bool FDelegateRegistry::AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
                                     MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New(
		InMonoObject, false);

	DelegateAddress2GarbageCollectionHandle.Emplace(
		FDelegateAddress{InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)}, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(GarbageCollectionHandle,
	                                                FDelegateAddress{
		                                                InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                                });

	return FCSharpEnvironment::GetEnvironment()->AddReference(InOwner, new FDelegateReference(GarbageCollectionHandle));
}

bool FDelegateRegistry::RemoveReference(const MonoObject* InMonoObject)
{
	if (const auto& FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InMonoObject))
	{
		if (FoundDelegateAddress->DelegateBaseHelper != nullptr)
		{
			delete FoundDelegateAddress->DelegateBaseHelper;

			FoundDelegateAddress->DelegateBaseHelper = nullptr;
		}

		DelegateAddress2GarbageCollectionHandle.Remove(*FoundDelegateAddress);

		GarbageCollectionHandle2DelegateAddress.Remove(InMonoObject);

		return true;
	}

	return false;
}

bool FDelegateRegistry::RemoveReference(const void* InAddress)
{
	for (auto& Pair : DelegateAddress2GarbageCollectionHandle)
	{
		if (Pair.Key == InAddress)
		{
			if (Pair.Key.DelegateBaseHelper != nullptr)
			{
				delete Pair.Key.DelegateBaseHelper;

				Pair.Key.DelegateBaseHelper = nullptr;
			}

			FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_Free(Pair.Value);

			GarbageCollectionHandle2DelegateAddress.Remove(Pair.Value);

			DelegateAddress2GarbageCollectionHandle.Remove(Pair.Key);

			return true;
		}
	}

	return false;
}

bool FDelegateRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto& FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InGarbageCollectionHandle))
	{
		if (FoundDelegateAddress->DelegateBaseHelper != nullptr)
		{
			delete FoundDelegateAddress->DelegateBaseHelper;

			FoundDelegateAddress->DelegateBaseHelper = nullptr;
		}

		DelegateAddress2GarbageCollectionHandle.Remove(*FoundDelegateAddress);

		GarbageCollectionHandle2DelegateAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
