#pragma once

#include "TValue.inl"
#include "TValueMapping.inl"

class FStringRegistry
{
public:
	template <typename T>
	struct TStringAddress : TValue<T>
	{
		TStringAddress(T InValue, const bool InNeedFree):
			TValue<T>(InValue),
			bNeedFree(InNeedFree)
		{
		}

		bool bNeedFree;
	};

	typedef TStringAddress<FName*> FNameAddress;

	typedef TStringAddress<FString*> FStringAddress;

	typedef TStringAddress<FText*> FTextAddress;

	template <typename Key, typename Value>
	struct TStringValueMapping : TValueMapping<Key, Value>
	{
	};

	typedef TStringValueMapping<void*, FNameAddress> FNameMapping;

	typedef TStringValueMapping<void*, FStringAddress> FStringMapping;

	typedef TStringValueMapping<void*, FTextAddress> FTextMapping;

	template <typename T>
	struct TStringRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q, typename R, R>
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
	FNameMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2NameAddress;

	FNameMapping::FKey2GarbageCollectionHandle NameAddress2GarbageCollectionHandle;

	FNameMapping::FMonoObject2Value MonoObject2NameAddress;

	FStringMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2StringAddress;

	FStringMapping::FKey2GarbageCollectionHandle StringAddress2GarbageCollectionHandle;

	FStringMapping::FMonoObject2Value MonoObject2StringAddress;

	FTextMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2TextAddress;

	FTextMapping::FKey2GarbageCollectionHandle TextAddress2GarbageCollectionHandle;

	FTextMapping::FMonoObject2Value MonoObject2TextAddress;
};

#include "FStringRegistry.inl"
