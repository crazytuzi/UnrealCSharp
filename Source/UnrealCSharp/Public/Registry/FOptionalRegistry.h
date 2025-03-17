#pragma once

#include "TValueMapping.inl"
#include "Reflection/Optional/FOptionalHelper.h"
#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
class UNREALCSHARP_API FOptionalRegistry
{
public:
	template <typename Key, typename Address>
	struct TOptionalValueMapping : TValueMapping<Key>
	{
		typedef Address FAddressType;

		typedef typename TValueMapping<FAddressType>::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
	};

	typedef TOptionalValueMapping<FOptionalHelper*, void*> FOptionalHelperValueMapping;

public:
	FOptionalRegistry();

	~FOptionalRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	FOptionalHelper* GetOptional(const FGarbageCollectionHandle& InGarbageCollectionHandle);

	MonoObject* GetObject(const FOptionalHelperValueMapping::FAddressType& InAddress);

	template <auto IsMember>
	auto AddReference(const FOptionalHelperValueMapping::FAddressType& InAddress,
	                  const FOptionalHelperValueMapping::ValueType& InValue, MonoObject* InMonoObject);

	bool RemoveReference(const FGarbageCollectionHandle& InGarbageCollectionHandle);

private:
	FOptionalHelperValueMapping::FGarbageCollectionHandle2Value OptionalGarbageCollectionHandle2Helper;

	FOptionalHelperValueMapping::FAddress2GarbageCollectionHandle OptionalAddress2GarbageCollectionHandle;
};

#include "FOptionalRegistry.inl"
#endif
