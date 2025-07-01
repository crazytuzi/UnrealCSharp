#pragma once

#include "TValueWrapper.inl"
#include "TValueMapping.inl"
#include "UEVersion.h"

class UNREALCSHARP_API FStringRegistry
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

#if UE_F_UTF8_STR_PROPERTY
	typedef TStringAddress<FUtf8String*> FUtf8StringAddress;
#endif

#if UE_F_ANSI_STR_PROPERTY
	typedef TStringAddress<FAnsiString*> FAnsiStringAddress;
#endif

	typedef TStringAddress<FText*> FTextAddress;

	template <typename Address, typename Value>
	struct TStringValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TStringValueMapping::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
	};

	typedef TStringValueMapping<void*, FNameAddress> FNameMapping;

	typedef TStringValueMapping<void*, FStringAddress> FStringMapping;

#if UE_F_UTF8_STR_PROPERTY
	typedef TStringValueMapping<void*, FUtf8StringAddress> FUtf8StringMapping;
#endif

#if UE_F_ANSI_STR_PROPERTY
	typedef TStringValueMapping<void*, FAnsiStringAddress> FAnsiStringMapping;
#endif

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

#if UE_F_UTF8_STR_PROPERTY
	FUtf8StringMapping::FGarbageCollectionHandle2Value Utf8StringGarbageCollectionHandle2Address;

	FUtf8StringMapping::FAddress2GarbageCollectionHandle Utf8StringAddress2GarbageCollectionHandle;
#endif

#if UE_F_ANSI_STR_PROPERTY
	FAnsiStringMapping::FGarbageCollectionHandle2Value AnsiStringGarbageCollectionHandle2Address;

	FAnsiStringMapping::FAddress2GarbageCollectionHandle AnsiStringAddress2GarbageCollectionHandle;
#endif

	FTextMapping::FGarbageCollectionHandle2Value TextGarbageCollectionHandle2Address;

	FTextMapping::FAddress2GarbageCollectionHandle TextAddress2GarbageCollectionHandle;
};

#include "FStringRegistry.inl"
