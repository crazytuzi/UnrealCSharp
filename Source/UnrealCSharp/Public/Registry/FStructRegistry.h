#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
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
	void* GetAddress(const MonoObject* InMonoObject);

	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct);

	MonoObject* GetObject(const void* InOwner, const void* InStruct);

	void* GetStruct(const MonoObject* InMonoObject);

	FGarbageCollectionHandle GetGarbageCollectionHandle(const void* InOwner, const void* InStruct);

public:
	bool AddReference(UScriptStruct* InScriptStruct, const void* InOwner, const void* InStruct,
	                  MonoObject* InMonoObject, bool bNeedFree = true);

	bool RemoveReference(const void* InOwner, const void* InStruct);

	bool RemoveReference(const MonoObject* InMonoObject);

private:
	TGarbageCollectionHandleMapping<FStructAddress> GarbageCollectionHandle2StructAddress;

	TMap<FStructAddressBase, FGarbageCollectionHandle> StructAddress2GarbageCollectionHandle;
};

#include "FStructRegistry.inl"
