#pragma once

#include "TValueMapping.inl"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

class UNREALCSHARP_API FDelegateRegistry
{
public:
	template <typename Address, typename Value>
	struct TDelegateValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TDelegateValueMapping::FKey2ManagedHandle FAddress2ManagedHandle;
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
	FDelegateHelperMapping::FManagedHandle2Value DelegateManagedHandle2Helper;

	FDelegateHelperMapping::FAddress2ManagedHandle DelegateAddress2ManagedHandle;

	FMulticastDelegateHelperMapping::FManagedHandle2Value MulticastDelegateManagedHandle2Helper;

	FMulticastDelegateHelperMapping::FAddress2ManagedHandle MulticastDelegateAddress2ManagedHandle;
};

#include "FDelegateRegistry.inl"
