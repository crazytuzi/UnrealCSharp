#pragma once

#include "TAddress.inl"
#include "TValueMapping.inl"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Container/FSetHelper.h"

template <typename T>
struct TContainerAddress : TAddress<T>
{
	using TAddress<T>::TAddress;
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
	template <typename Key>
	struct TContainerValueMapping : TValueMapping<Key>
	{
		typedef TMap<void*, typename TValueMapping<Key>::GarbageCollectionHandle2Value::KeyType>
		Address2GarbageCollectionHandle;
	};

	typedef TContainerValueMapping<FArrayHelperAddress> FArrayHelperValueMapping;

	typedef TContainerValueMapping<FMapHelperAddress> FMapHelperValueMapping;

	typedef TContainerValueMapping<FSetHelperAddress> FSetHelperValueMapping;

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
	FArrayHelperValueMapping::GarbageCollectionHandle2Value GarbageCollectionHandle2ArrayHelperAddress;

	FArrayHelperValueMapping::Value2GarbageCollectionHandle ArrayHelperAddress2GarbageCollectionHandle;

	FArrayHelperValueMapping::MonoObject2Value MonoObject2ArrayHelperAddress;

	FArrayHelperValueMapping::Address2GarbageCollectionHandle ArrayAddress2GarbageCollectionHandle;

	FMapHelperValueMapping::GarbageCollectionHandle2Value GarbageCollectionHandle2MapHelperAddress;

	FMapHelperValueMapping::Value2GarbageCollectionHandle MapHelperAddress2GarbageCollectionHandle;

	FMapHelperValueMapping::MonoObject2Value MonoObject2MapHelperAddress;

	FMapHelperValueMapping::Address2GarbageCollectionHandle MapAddress2GarbageCollectionHandle;

	FSetHelperValueMapping::GarbageCollectionHandle2Value GarbageCollectionHandle2SetHelperAddress;

	FSetHelperValueMapping::Value2GarbageCollectionHandle SetHelperAddress2GarbageCollectionHandle;

	FSetHelperValueMapping::MonoObject2Value MonoObject2SetHelperAddress;

	FSetHelperValueMapping::Address2GarbageCollectionHandle SetAddress2GarbageCollectionHandle;
};

#include "FContainerRegistry.inl"
