#include "Registry/FDelegateRegistry.h"
#include "Reference/FDelegateReference.h"

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

bool FDelegateRegistry::AddReference(const TGarbageCollectionHandle<>& InOwner, void* InDelegate,
                                     FDelegateBaseHelper* InDelegateBaseHelper,
                                     MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New(
		InMonoObject, false);

	DelegateAddress2GarbageCollectionHandle.Emplace(FDelegateAddress{InDelegate, InDelegateBaseHelper},
	                                                GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(GarbageCollectionHandle,
	                                                FDelegateAddress{InDelegate, InDelegateBaseHelper});

	return FCSharpEnvironment::GetEnvironment()->AddReference(InOwner, new FDelegateReference(GarbageCollectionHandle));
}

bool FDelegateRegistry::RemoveReference(const TGarbageCollectionHandle<>& InGarbageCollectionHandle)
{
	if (const auto FoundDelegateAddress = GarbageCollectionHandle2DelegateAddress.Find(InGarbageCollectionHandle))
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
