#pragma once

#include "TValueWrapper.inl"
#include "TValueMapping.inl"
#include "Domain/Script/IManagedHandle.h"

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
		typedef typename TStructMapping::FKey2ManagedHandle FAddress2ManagedHandle;
	};

	typedef TStructMapping<FStructAddressBase, FStructAddress> FStructMapping;

public:
	FStructRegistry();

	~FStructRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	void* GetAddress(const IManagedHandle InManagedHandle);

	void* GetAddress(const IManagedHandle InManagedHandle, UStruct*& InStruct);

	IManagedHandle GetObject(UScriptStruct* InScriptStruct, const void* InStruct);

	void* GetStruct(const IManagedHandle InManagedHandle);

	IManagedHandle GetManagedHandle(UScriptStruct* InScriptStruct, const void* InStruct);

public:
	template <auto IsNeedFree>
	auto AddReference(UScriptStruct* InScriptStruct, const void* InStruct, const IManagedHandle InManagedHandle);

	bool AddReference(const IManagedHandle InOwner, UScriptStruct* InScriptStruct,
	                  const void* InStruct, const IManagedHandle InManagedHandle);

	bool RemoveReference(const IManagedHandle InManagedHandle);

private:
	FStructMapping::FManagedHandle2Value ManagedHandle2StructAddress;

	FStructMapping::FAddress2ManagedHandle StructAddress2ManagedHandle;
};

#include "FStructRegistry.inl"
