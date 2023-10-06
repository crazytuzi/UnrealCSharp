#pragma once

#include "TValue.inl"
#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

struct FStructAddressBase : TAddressValue<TWeakObjectPtr<UScriptStruct>>
{
	FStructAddressBase(UScriptStruct* InScriptStruct, void* InAddress):
		TAddressValue(InScriptStruct, InAddress)
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

		FStructAddress(UScriptStruct* InScriptStruct, void* InAddress, const bool InNeedFree):
			FStructAddressBase(InScriptStruct, InAddress),
			bNeedFree(InNeedFree)
		{
		}
	};

	template <typename Key, typename Value>
	struct TStructMapping : TValueMapping<Key, Value>
	{
	};

	typedef TStructMapping<FStructAddressBase, FStructAddress> FStructMapping;

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
	FStructMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2StructAddress;

	FStructMapping::FKey2GarbageCollectionHandle StructAddress2GarbageCollectionHandle;

	FStructMapping::FMonoObject2Value MonoObject2StructAddress;
};

#include "FStructRegistry.inl"
