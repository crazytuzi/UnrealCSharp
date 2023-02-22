#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.h"
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
	auto GetDelegate(const MonoObject* InMonoObject);

	template <typename T>
	auto GetObject(const T* InDelegate);

	bool AddReference(const TGarbageCollectionHandle<>& InOwner, void* InDelegate,
	                  FDelegateBaseHelper* InDelegateBaseHelper, MonoObject* InMonoObject);

	bool RemoveReference(const TGarbageCollectionHandle<>& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FDelegateAddress> GarbageCollectionHandle2DelegateAddress;

	TMap<FDelegateAddress, TGarbageCollectionHandle<>> DelegateAddress2GarbageCollectionHandle;
};

#include "FDelegateRegistry.inl"
