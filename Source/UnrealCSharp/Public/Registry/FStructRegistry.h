#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"
#include "mono/metadata/object-forward.h"

struct FStructAddressBase
{
	void* Owner;

	void* Address;

	FStructAddressBase(void* InOwner, void* InAddress):
		Owner(InOwner),
		Address(InAddress)
	{
	}
};

static bool operator==(const FStructAddressBase& A, const FStructAddressBase& B);

static uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase);

class FStructRegistry
{
private:
	struct FStructAddress : FStructAddressBase
	{
		TWeakObjectPtr<UScriptStruct> ScriptStruct;

		bool bNeedFree;

		FStructAddress(void* InOwner, void* InAddress, UScriptStruct* InScriptStruct, const bool InbNeedFree):
			FStructAddressBase(InOwner, InAddress),
			ScriptStruct(InScriptStruct),
			bNeedFree(InbNeedFree)
		{
		}
	};

public:
	FStructRegistry();

	~FStructRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	void* GetAddress(const MonoObject* InMonoObject);

	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct);

	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct);

	MonoObject* GetObject(const void* InOwner, const void* InStruct);

	void* GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	void* GetStruct(const MonoObject* InMonoObject);

	FGarbageCollectionHandle GetGarbageCollectionHandle(const void* InOwner, const void* InStruct);

public:
	bool AddReference(UScriptStruct* InScriptStruct, const void* InOwner, const void* InStruct,
	                  MonoObject* InMonoObject, bool bNeedFree = true);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FStructAddress> GarbageCollectionHandle2StructAddress;

	TMap<FStructAddressBase, FGarbageCollectionHandle> StructAddress2GarbageCollectionHandle;

	TMonoObjectMapping<FStructAddress> MonoObject2StructAddress;
};

#include "FStructRegistry.inl"
