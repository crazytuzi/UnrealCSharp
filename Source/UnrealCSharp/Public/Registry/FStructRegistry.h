#pragma once

#include "TValue.inl"
#include "TValueMapping.inl"
#include "mono/metadata/object-forward.h"

class FStructRegistry
{
private:
	struct FStructAddressBase : TValue<TWeakObjectPtr<UScriptStruct>>
	{
		FStructAddressBase(UScriptStruct* InScriptStruct, void* InAddress):
			TValue(InScriptStruct),
			Address(InAddress)
		{
		}

		void* Address;
	};

	friend bool operator==(const FStructAddressBase& A, const FStructAddressBase& B)
	{
		return A.Value == B.Value && A.Address == B.Address;
	}

	friend static uint32 GetTypeHash(const FStructAddressBase& InStructAddressBase)
	{
		return HashCombineFast(GetTypeHash(InStructAddressBase.Value), GetTypeHash(InStructAddressBase.Address));
	}
	
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
	bool AddReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject,
	                  bool bNeedFree = true);

	bool AddReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct, const void* InStruct,
	                  MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FStructMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2StructAddress;

	FStructMapping::FAddress2GarbageCollectionHandle StructAddress2GarbageCollectionHandle;
};
