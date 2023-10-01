#pragma once

#include "TValue.inl"
#include "TValueMapping.inl"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Container/FSetHelper.h"

template <typename T>
struct TContainerAddress : TAddressValue<T>
{
	using TAddressValue<T>::TAddressValue;
};

typedef TContainerAddress<FArrayHelper*> FArrayHelperAddress;

typedef TContainerAddress<FMapHelper*> FMapHelperAddress;

typedef TContainerAddress<FSetHelper*> FSetHelperAddress;

static bool operator==(const FArrayHelperAddress& A, const FArrayHelperAddress& B);

static bool operator==(const FMapHelperAddress& A, const FMapHelperAddress& B);

static bool operator==(const FSetHelperAddress& A, const FSetHelperAddress& B);

static uint32 GetTypeHash(const FArrayHelperAddress& InArrayHelperAddress);

static uint32 GetTypeHash(const FMapHelperAddress& InMapHelperAddress);

static uint32 GetTypeHash(const FSetHelperAddress& InSetHelperAddress);

class FContainerRegistry
{
public:
	template <typename Key, typename Address>
	struct TContainerValueMapping : TValueMapping<Key>
	{
		typedef Address FAddressType;

		typedef TMap<FAddressType, typename TValueMapping<Key>::FGarbageCollectionHandle2Value::KeyType>
		FAddress2GarbageCollectionHandle;
	};

	typedef TContainerValueMapping<FArrayHelperAddress, void*> FArrayHelperValueMapping;

	typedef TContainerValueMapping<FMapHelperAddress, void*> FMapHelperValueMapping;

	typedef TContainerValueMapping<FSetHelperAddress, void*> FSetHelperValueMapping;

	template <typename T>
	struct TContainerRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q, typename R, R, typename S, S>
	struct TContainerRegistryImplementation
	{
	};

public:
	FContainerRegistry();

	~FContainerRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	FArrayHelperValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2ArrayHelperAddress;

	FArrayHelperValueMapping::FKey2GarbageCollectionHandle ArrayHelperAddress2GarbageCollectionHandle;

	FArrayHelperValueMapping::FMonoObject2Value MonoObject2ArrayHelperAddress;

	FArrayHelperValueMapping::FAddress2GarbageCollectionHandle ArrayAddress2GarbageCollectionHandle;

	FMapHelperValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2MapHelperAddress;

	FMapHelperValueMapping::FKey2GarbageCollectionHandle MapHelperAddress2GarbageCollectionHandle;

	FMapHelperValueMapping::FMonoObject2Value MonoObject2MapHelperAddress;

	FMapHelperValueMapping::FAddress2GarbageCollectionHandle MapAddress2GarbageCollectionHandle;

	FSetHelperValueMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2SetHelperAddress;

	FSetHelperValueMapping::FKey2GarbageCollectionHandle SetHelperAddress2GarbageCollectionHandle;

	FSetHelperValueMapping::FMonoObject2Value MonoObject2SetHelperAddress;

	FSetHelperValueMapping::FAddress2GarbageCollectionHandle SetAddress2GarbageCollectionHandle;
};

#include "FContainerRegistry.inl"
