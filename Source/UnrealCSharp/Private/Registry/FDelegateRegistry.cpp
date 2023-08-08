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

		FGarbageCollectionHandle::Free(Pair.Key);
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
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, false);

	DelegateAddress2GarbageCollectionHandle.Emplace(
		FDelegateAddress{InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)}, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                FDelegateAddress{
		                                                InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                                });

	return true;
}

bool FDelegateRegistry::AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
                                     MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, false);

	DelegateAddress2GarbageCollectionHandle.Emplace(
		FDelegateAddress{InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)}, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(MoveTemp(GarbageCollectionHandle),
	                                                FDelegateAddress{
		                                                InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                                });

	return FCSharpEnvironment::GetEnvironment().AddReference(InOwner, new FDelegateReference(GarbageCollectionHandle));
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
