#include "Registry/FDelegateRegistry.h"

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
	// @TODO
}

bool FDelegateRegistry::AddReference(void* InDelegate, FDelegateBaseHelper* InDelegateBaseHelper,
                                     MonoObject* InMonoObject)
{
	auto GarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetDomain()->GCHandle_New_WeakRef(
		InMonoObject, true);

	DelegateAddress2GarbageCollectionHandle.Emplace(FDelegateAddress{InDelegate, InDelegateBaseHelper},
	                                                GarbageCollectionHandle);

	GarbageCollectionHandle2DelegateAddress.Emplace(GarbageCollectionHandle,
	                                                FDelegateAddress{InDelegate, InDelegateBaseHelper});

	return true;
}
