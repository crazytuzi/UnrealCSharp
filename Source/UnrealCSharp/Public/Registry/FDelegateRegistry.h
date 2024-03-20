#pragma once

#include "TValueMapping.inl"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

class FDelegateRegistry
{
public:
	template <typename Address, typename Value>
	struct TDelegateValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TDelegateValueMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
	};

	typedef TDelegateValueMapping<void*, FDelegateHelper*> FDelegateHelperMapping;

	typedef TDelegateValueMapping<void*, FMulticastDelegateHelper*> FMulticastDelegateHelperMapping;

	template <typename T>
	struct TDelegateRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q>
	struct TDelegateRegistryImplementation
	{
	};

public:
	FDelegateRegistry();

	~FDelegateRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	FDelegateHelperMapping::FGarbageCollectionHandle2Value DelegateGarbageCollectionHandle2Helper;

	FDelegateHelperMapping::FAddress2GarbageCollectionHandle DelegateAddress2GarbageCollectionHandle;

	FMulticastDelegateHelperMapping::FGarbageCollectionHandle2Value MulticastDelegateGarbageCollectionHandle2Helper;

	FMulticastDelegateHelperMapping::FAddress2GarbageCollectionHandle MulticastDelegateAddress2GarbageCollectionHandle;
};

#include "FDelegateRegistry.inl"
