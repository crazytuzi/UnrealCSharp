#pragma once

#include "TAddress.inl"
#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

struct FStructAddressBase : TAddress<TWeakObjectPtr<UScriptStruct>>
{
	FStructAddressBase(void* InAddress, UScriptStruct* InScriptStruct):
		TAddress(InAddress, InScriptStruct)
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

		FStructAddress(void* InAddress, UScriptStruct* InScriptStruct, const bool InNeedFree):
			FStructAddressBase(InAddress, InScriptStruct),
			bNeedFree(InNeedFree)
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
	TValueMapping<FStructAddressBase, FStructAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2StructAddress;

	TValueMapping<FStructAddressBase, FStructAddress>::Value2GarbageCollectionHandle
	StructAddress2GarbageCollectionHandle;

	TValueMapping<FStructAddressBase, FStructAddress>::MonoObject2Value MonoObject2StructAddress;
};

#include "FStructRegistry.inl"
