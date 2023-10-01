#pragma once

#include "TValue.inl"
#include "TValueMapping.inl"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

class FDelegateRegistry
{
public:
	template <typename T>
	struct TDelegateAddress : TAddressValue<T>
	{
		using TAddressValue<T>::TAddressValue;
	};

	typedef TDelegateAddress<FDelegateHelper*> FDelegateHelperAddress;

	typedef TDelegateAddress<FMulticastDelegateHelper*> FMulticastDelegateHelperAddress;

	template <typename Key, typename Value>
	struct TDelegateValueMapping : TValueMapping<Key, Value>
	{
	};

	typedef TDelegateValueMapping<void*, FDelegateHelperAddress> FDelegateHelperMapping;

	typedef TDelegateValueMapping<void*, FMulticastDelegateHelperAddress> FMulticastDelegateHelperMapping;

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
	FDelegateHelperMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2DelegateHelperAddress;

	FDelegateHelperMapping::FKey2GarbageCollectionHandle DelegateAddress2GarbageCollectionHandle;

	FMulticastDelegateHelperMapping::FGarbageCollectionHandle2Value
	GarbageCollectionHandle2MulticastDelegateHelperAddress;

	FMulticastDelegateHelperMapping::FKey2GarbageCollectionHandle MulticastDelegateAddress2GarbageCollectionHandle;
};

#include "FDelegateRegistry.inl"
