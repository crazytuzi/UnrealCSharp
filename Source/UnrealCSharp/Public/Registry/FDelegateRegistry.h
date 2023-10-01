#pragma once

#include "TAddress.inl"
#include "TValueMapping.inl"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

class FDelegateRegistry
{
public:
	template <typename T>
	struct TDelegateAddress : TAddress<T>
	{
		using TAddress<T>::TAddress;
	};

	typedef TDelegateAddress<FDelegateHelper*> FDelegateHelperAddress;

	typedef TDelegateAddress<FMulticastDelegateHelper*> FMulticastDelegateHelperAddress;

	typedef TValueMapping<void*, FDelegateHelperAddress> FDelegateHelperMapping;

	typedef TValueMapping<void*, FMulticastDelegateHelperAddress> FMulticastDelegateHelperMapping;

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
	FDelegateHelperMapping::GarbageCollectionHandle2Value GarbageCollectionHandle2DelegateHelperAddress;

	FDelegateHelperMapping::Value2GarbageCollectionHandle DelegateHelperAddress2GarbageCollectionHandle;

	FMulticastDelegateHelperMapping::GarbageCollectionHandle2Value
	GarbageCollectionHandle2MulticastDelegateHelperAddress;

	FMulticastDelegateHelperMapping::Value2GarbageCollectionHandle
	MulticastDelegateHelperAddress2GarbageCollectionHandle;
};

#include "FDelegateRegistry.inl"
