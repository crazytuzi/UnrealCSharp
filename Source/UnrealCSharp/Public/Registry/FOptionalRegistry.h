#pragma once

#include "TValueMapping.inl"
#include "Reflection/Optional/FOptionalHelper.h"
#include "Domain/Script/IManagedHandle.h"
#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
class UNREALCSHARP_API FOptionalRegistry
{
public:
	template <typename Key, typename Address>
	struct TOptionalValueMapping : TValueMapping<Key>
	{
		typedef Address FAddressType;

		typedef typename TValueMapping<FAddressType>::FKey2ManagedHandle FAddress2ManagedHandle;
	};

	typedef TOptionalValueMapping<FOptionalHelper*, void*> FOptionalHelperValueMapping;

public:
	FOptionalRegistry();

	~FOptionalRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	FOptionalHelper* GetOptional(const IManagedHandle InManagedHandle);

	IManagedHandle GetObject(const FOptionalHelperValueMapping::FAddressType& InAddress);

	template <auto IsMember>
	auto AddReference(const FOptionalHelperValueMapping::FAddressType& InAddress,
	                  const FOptionalHelperValueMapping::ValueType& InValue,
	                  FClassReflection* InClass, const IManagedHandle InManagedHandle);

	bool RemoveReference(const IManagedHandle InManagedHandle);

private:
	FOptionalHelperValueMapping::FManagedHandle2Value ManagedHandle2Helper;

	FOptionalHelperValueMapping::FAddress2ManagedHandle Address2ManagedHandle;
};

#include "FOptionalRegistry.inl"
#endif
