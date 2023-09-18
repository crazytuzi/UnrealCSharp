#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "GarbageCollection/TMonoObjectMapping.inl"
#include "mono/metadata/object-forward.h"

struct FStructAddressBase
{
	TWeakObjectPtr<UScriptStruct> ScriptStruct;

	void* Address;

	FStructAddressBase(UScriptStruct* InScriptStruct, void* InAddress):
		ScriptStruct(InScriptStruct),
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
		bool bNeedFree;

		FStructAddress(UScriptStruct* InScriptStruct, void* InAddress, const bool InbNeedFree):
			FStructAddressBase(InScriptStruct, InAddress),
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

	MonoObject* GetObject(UScriptStruct* InScriptStruct, const void* InStruct);

	void* GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	void* GetStruct(const MonoObject* InMonoObject);

	FGarbageCollectionHandle GetGarbageCollectionHandle(UScriptStruct* InScriptStruct, const void* InStruct);

public:
	bool AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject,
	                  bool bNeedFree = true);

	bool AddReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct, const void* InStruct,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	TGarbageCollectionHandleMapping<FStructAddress> GarbageCollectionHandle2StructAddress;

	TMap<FStructAddressBase, FGarbageCollectionHandle> StructAddress2GarbageCollectionHandle;

	TMonoObjectMapping<FStructAddress> MonoObject2StructAddress;
};

#include "FStructRegistry.inl"
