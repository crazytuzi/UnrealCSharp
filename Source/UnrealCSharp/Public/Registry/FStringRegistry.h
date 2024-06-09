#pragma once

#include "TValueWrapper.inl"
#include "TValueMapping.inl"

class FStringRegistry
{
public:
	template <typename T>
	struct TStringAddress : TValueWrapper<T>
	{
		TStringAddress(T InValue, const bool InNeedFree):
			TValueWrapper<T>(InValue),
			bNeedFree(InNeedFree)
		{
		}

		bool bNeedFree;
	};

	typedef TStringAddress<FName*> FNameAddress;

	typedef TStringAddress<FString*> FStringAddress;

	typedef TStringAddress<FText*> FTextAddress;

	template <typename Address, typename Value>
	struct TStringValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TStringValueMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
	};

	typedef TStringValueMapping<void*, FNameAddress> FNameMapping;

	typedef TStringValueMapping<void*, FStringAddress> FStringMapping;

	typedef TStringValueMapping<void*, FTextAddress> FTextMapping;

	template <typename T>
	struct TStringRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q>
	struct TStringRegistryImplementation
	{
	};

public:
	FStringRegistry();

	~FStringRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	FNameMapping::FGarbageCollectionHandle2Value NameGarbageCollectionHandle2Address;

	FNameMapping::FAddress2GarbageCollectionHandle NameAddress2GarbageCollectionHandle;

	FStringMapping::FGarbageCollectionHandle2Value StringGarbageCollectionHandle2Address;

	FStringMapping::FAddress2GarbageCollectionHandle StringAddress2GarbageCollectionHandle;

	FTextMapping::FGarbageCollectionHandle2Value TextGarbageCollectionHandle2Address;

	FTextMapping::FAddress2GarbageCollectionHandle TextAddress2GarbageCollectionHandle;
};

#include "FStringRegistry.inl"
