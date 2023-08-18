#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"

struct FBindingAddress
{
	void* Address;

	bool bNeedFree;

	FBindingAddress(void* InAddress, const bool InNeedFree = true):
		Address(InAddress),
		bNeedFree(InNeedFree)
	{
	}
};

static bool operator==(const FBindingAddress& A, const FBindingAddress& B);

static uint32 GetTypeHash(const FBindingAddress& InBindingAddress);

class UNREALCSHARP_API FBindingRegistry
{
public:
	FBindingRegistry();

	~FBindingRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoObject* GetObject(const void* InObject);

	void* GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle);

public:
	bool AddReference(const void* InObject, MonoObject* InMonoObject, bool bNeedFree = true);

	template <typename T>
	auto RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FBindingAddress> GarbageCollectionHandle2BindingAddress;

	TMap<FBindingAddress, FGarbageCollectionHandle> BindingAddress2GarbageCollectionHandle;
};

#include "FBindingRegistry.inl"
