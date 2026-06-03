#pragma once

#include "TValueMapping.inl"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Container/FMapHelper.h"
#include "Reflection/Container/FSetHelper.h"

class UNREALCSHARP_API FContainerRegistry
{
public:
	template <typename Key, typename Address>
	struct TContainerValueMapping : TValueMapping<Key>
	{
		typedef Address FAddressType;

		typedef typename TValueMapping<FAddressType>::FKey2ManagedHandle FAddress2ManagedHandle;
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
	FArrayHelperValueMapping::FManagedHandle2Value ArrayManagedHandle2Helper;

	FArrayHelperValueMapping::FAddress2ManagedHandle ArrayAddress2ManagedHandle;

	FMapHelperValueMapping::FManagedHandle2Value MapManagedHandle2Helper;

	FMapHelperValueMapping::FAddress2ManagedHandle MapAddress2ManagedHandle;

	FSetHelperValueMapping::FManagedHandle2Value SetManagedHandle2Helper;

	FSetHelperValueMapping::FAddress2ManagedHandle SetAddress2ManagedHandle;
};

#include "FContainerRegistry.inl"
