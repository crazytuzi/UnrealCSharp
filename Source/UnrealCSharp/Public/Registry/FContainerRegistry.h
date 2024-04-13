#pragma once

#include "TValueMapping.inl"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Container/FSetHelper.h"

class FContainerRegistry
{
public:
	template <typename Key, typename Address>
	struct TContainerValueMapping : TValueMapping<Key>
	{
		typedef Address FAddressType;

		typedef typename TValueMapping<FAddressType>::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
	};

	typedef TContainerValueMapping<FArrayHelper*, void*> FArrayHelperValueMapping;

	typedef TContainerValueMapping<FMapHelper*, void*> FMapHelperValueMapping;

	typedef TContainerValueMapping<FSetHelper*, void*> FSetHelperValueMapping;

	template <typename T>
	struct TContainerRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q>
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
	FArrayHelperValueMapping::FGarbageCollectionHandle2Value ArrayGarbageCollectionHandle2Helper;

	FArrayHelperValueMapping::FAddress2GarbageCollectionHandle ArrayAddress2GarbageCollectionHandle;

	FMapHelperValueMapping::FGarbageCollectionHandle2Value MapGarbageCollectionHandle2Helper;

	FMapHelperValueMapping::FAddress2GarbageCollectionHandle MapAddress2GarbageCollectionHandle;

	FSetHelperValueMapping::FGarbageCollectionHandle2Value SetGarbageCollectionHandle2Helper;

	FSetHelperValueMapping::FAddress2GarbageCollectionHandle SetAddress2GarbageCollectionHandle;
};

#include "FContainerRegistry.inl"
