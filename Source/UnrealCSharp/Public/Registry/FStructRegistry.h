#pragma once

#include "TValueWrapper.inl"
#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

struct FStructAddressBase : TValueWrapper<TWeakObjectPtr<UScriptStruct>>
{
	FStructAddressBase(UScriptStruct* InScriptStruct, void* InAddress):
		TValueWrapper(InScriptStruct),
		Address(InAddress)
	{
	}

	void* Address;
};

static bool operator==(const FStructAddressBase& A, const FStructAddressBase& B);

static uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase);

class UNREALCSHARP_API FStructRegistry
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
		typedef typename TStructMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
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

	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct);

	MonoObject* GetObject(UScriptStruct* InScriptStruct, const void* InStruct);

	void* GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	FGarbageCollectionHandle GetGarbageCollectionHandle(UScriptStruct* InScriptStruct, const void* InStruct);

public:
	template <auto IsNeedFree>
	auto AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject);

	bool AddReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
	                  const void* InStruct, MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FStructMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2StructAddress;

	FStructMapping::FAddress2GarbageCollectionHandle StructAddress2GarbageCollectionHandle;
};

#include "FStructRegistry.inl"
