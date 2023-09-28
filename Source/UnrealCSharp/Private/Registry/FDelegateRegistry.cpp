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
		if (Pair.Value.Value != nullptr)
		{
			delete Pair.Value.Value;

			Pair.Value.Value = nullptr;
		}

		FGarbageCollectionHandle::Free(Pair.Key);
	}

	GarbageCollectionHandle2DelegateAddress.Empty();

	Address2GarbageCollectionHandle.Empty();
}

MonoObject* FDelegateRegistry::GetObject(const void* InAddress)
{
	if (const auto GarbageCollectionHandle = Address2GarbageCollectionHandle.Find(InAddress))
	{
		return *GarbageCollectionHandle;
	}

	return nullptr;
}

bool FDelegateRegistry::AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewWeakRef(InMonoObject, true);

	Address2GarbageCollectionHandle.Add(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Add(GarbageCollectionHandle,
	                                            FDelegateAddress{
		                                            InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                            });

	return true;
}

bool FDelegateRegistry::AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
                                     MonoObject* InMonoObject)
{
	const auto GarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InMonoObject, true);

	Address2GarbageCollectionHandle.Add(InAddress, GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Add(GarbageCollectionHandle,
	                                            FDelegateAddress{
		                                            InAddress, static_cast<FDelegateBaseHelper*>(InDelegate)
	                                            });

	return FCSharpEnvironment::GetEnvironment().AddReference(InOwner, new FDelegateReference(GarbageCollectionHandle));
}

bool FDelegateRegistry::RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle)
{
	if (const auto& FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InGarbageCollectionHandle))
	{
		Address2GarbageCollectionHandle.Remove(FoundDelegateAddress->Address);

		if (FoundDelegateAddress->Value != nullptr)
		{
			delete FoundDelegateAddress->Value;

			FoundDelegateAddress->Value = nullptr;
		}

		GarbageCollectionHandle2DelegateAddress.Remove(InGarbageCollectionHandle);

		return true;
	}

	return false;
}
