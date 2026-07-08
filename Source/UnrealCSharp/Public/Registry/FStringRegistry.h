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

		typedef typename TStringValueMapping::FKey2ManagedHandle FAddress2ManagedHandle;
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
	FNameMapping::FManagedHandle2Value NameManagedHandle2Address;

	FNameMapping::FAddress2ManagedHandle NameAddress2ManagedHandle;

	FStringMapping::FManagedHandle2Value StringManagedHandle2Address;

	FStringMapping::FAddress2ManagedHandle StringAddress2ManagedHandle;

#if UE_F_UTF8_STR_PROPERTY
	FUtf8StringMapping::FManagedHandle2Value Utf8StringManagedHandle2Address;

	FUtf8StringMapping::FAddress2ManagedHandle Utf8StringAddress2ManagedHandle;
#endif

#if UE_F_ANSI_STR_PROPERTY
	FAnsiStringMapping::FManagedHandle2Value AnsiStringManagedHandle2Address;

	FAnsiStringMapping::FAddress2ManagedHandle AnsiStringAddress2ManagedHandle;
#endif

	FTextMapping::FManagedHandle2Value TextManagedHandle2Address;

	FTextMapping::FAddress2ManagedHandle TextAddress2ManagedHandle;
};

#include "FStringRegistry.inl"
