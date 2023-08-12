#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "Reflection/Delegate/FDelegateBaseHelper.h"
#include "mono/metadata/object-forward.h"

struct FDelegateAddress
{
	void* Address;

	FDelegateBaseHelper* DelegateBaseHelper;
};

static bool operator==(const FDelegateAddress& A, const FDelegateAddress& B);

static bool operator==(const FDelegateAddress& A, const void* B);

static uint32 GetTypeHash(const FDelegateAddress& InDelegateAddress);

class FDelegateRegistry
{
public:
	FDelegateRegistry();

	~FDelegateRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	template <typename T>
	auto GetDelegate(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	MonoObject* GetObject(const void* InAddress);

	bool AddReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject);

	bool AddReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FDelegateAddress> GarbageCollectionHandle2DelegateAddress;

	TMap<FDelegateAddress, FGarbageCollectionHandle> DelegateAddress2GarbageCollectionHandle;

	TMap<void*, FGarbageCollectionHandle> Address2GarbageCollectionHandle;

	TMap<MonoObject*, FGarbageCollectionHandle> MonoObject2GarbageCollectionHandleMap;
};

#include "FDelegateRegistry.inl"
