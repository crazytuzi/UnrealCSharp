#pragma once

#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTScriptInterface.inl"
#include "TValueWrapper.inl"
#include "TValueMapping.inl"

class UNREALCSHARP_API FMultiRegistry
{
public:
	template <typename T, template<typename...> class IsType>
	struct TMultiAddress : TValueWrapper<T>
	{
		template <typename U>
		struct TIsType
		{
			enum { value = IsType<U>::Value };
		};

		TMultiAddress(T InValue, const bool InNeedFree):
			TValueWrapper<T>(InValue),
			bNeedFree(InNeedFree)
		{
		}

		bool bNeedFree;
	};

	typedef TMultiAddress<TSubclassOf<UObject>*, TIsTSubclassOf> FSubclassOfAddress;

	typedef TMultiAddress<TWeakObjectPtr<UObject>*, TIsTWeakObjectPtr> FWeakObjectPtrAddress;

	typedef TMultiAddress<TLazyObjectPtr<UObject>*, TIsTLazyObjectPtr> FLazyObjectPtrAddress;

	typedef TMultiAddress<TSoftObjectPtr<UObject>*, TIsTSoftObjectPtr> FSoftObjectPtrAddress;

	typedef TMultiAddress<TScriptInterface<IInterface>*, TIsTScriptInterface> FScriptInterfaceAddress;

	typedef TMultiAddress<TSoftClassPtr<UObject>*, TIsTSoftClassPtr> FSoftClassPtrAddress;

	template <typename Address, typename Value>
	struct TMultiValueMapping : TValueMapping<Address, Value>
	{
		typedef Address FAddressType;

		typedef typename TValueMapping<FAddressType>::FKey2ManagedHandle FAddress2ManagedHandle;
	};

	typedef TMultiValueMapping<void*, FSubclassOfAddress> FSubclassOfMapping;

	typedef TMultiValueMapping<void*, FWeakObjectPtrAddress> FWeakObjectPtrMapping;

	typedef TMultiValueMapping<void*, FLazyObjectPtrAddress> FLazyObjectPtrMapping;

	typedef TMultiValueMapping<void*, FSoftObjectPtrAddress> FSoftObjectPtrMapping;

	typedef TMultiValueMapping<void*, FScriptInterfaceAddress> FScriptInterfaceMapping;

	typedef TMultiValueMapping<void*, FSoftClassPtrAddress> FSoftClassPtrMapping;

	template <typename T, typename U = T>
	struct TMultiRegistry
	{
	};

	template <typename T, typename P, P, typename Q, Q>
	struct TMultiRegistryImplementation
	{
	};

public:
	FMultiRegistry();

	~FMultiRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	FSubclassOfMapping::FManagedHandle2Value SubclassOfManagedHandle2Address;

	FSubclassOfMapping::FAddress2ManagedHandle SubclassOfAddress2ManagedHandle;

	FWeakObjectPtrMapping::FManagedHandle2Value WeakObjectPtrManagedHandle2Address;

	FWeakObjectPtrMapping::FAddress2ManagedHandle WeakObjectPtrAddress2ManagedHandle;

	FLazyObjectPtrMapping::FManagedHandle2Value LazyObjectPtrManagedHandle2Address;

	FLazyObjectPtrMapping::FAddress2ManagedHandle LazyObjectPtrAddress2ManagedHandle;

	FSoftObjectPtrMapping::FManagedHandle2Value SoftObjectPtrManagedHandle2Address;

	FSoftObjectPtrMapping::FAddress2ManagedHandle SoftObjectPtrAddress2ManagedHandle;

	FScriptInterfaceMapping::FManagedHandle2Value ScriptInterfaceManagedHandle2Address;

	FScriptInterfaceMapping::FKey2ManagedHandle ScriptInterfaceAddress2ManagedHandle;

	FSoftClassPtrMapping::FManagedHandle2Value SoftClassPtrManagedHandle2Address;

	FSoftClassPtrMapping::FAddress2ManagedHandle SoftClassPtrAddress2ManagedHandle;
};

#include "FMultiRegistry.inl"
