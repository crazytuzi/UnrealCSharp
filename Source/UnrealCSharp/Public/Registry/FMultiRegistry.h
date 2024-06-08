#pragma once

#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTScriptInterface.inl"
#include "TValueWrapper.inl"
#include "TValueMapping.inl"

class FMultiRegistry
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

		typedef typename TValueMapping<FAddressType>::FKey2GarbageCollectionHandle FAddress2GarbageCollectionHandle;
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
	FSubclassOfMapping::FGarbageCollectionHandle2Value SubclassOfGarbageCollectionHandle2Address;

	FSubclassOfMapping::FAddress2GarbageCollectionHandle SubclassOfAddress2GarbageCollectionHandle;

	FWeakObjectPtrMapping::FGarbageCollectionHandle2Value WeakObjectPtrGarbageCollectionHandle2Address;

	FWeakObjectPtrMapping::FAddress2GarbageCollectionHandle WeakObjectPtrAddress2GarbageCollectionHandle;

	FLazyObjectPtrMapping::FGarbageCollectionHandle2Value LazyObjectPtrGarbageCollectionHandle2Address;

	FLazyObjectPtrMapping::FAddress2GarbageCollectionHandle LazyObjectPtrAddress2GarbageCollectionHandle;

	FSoftObjectPtrMapping::FGarbageCollectionHandle2Value SoftObjectPtrGarbageCollectionHandle2Address;

	FSoftObjectPtrMapping::FAddress2GarbageCollectionHandle SoftObjectPtrAddress2GarbageCollectionHandle;

	FScriptInterfaceMapping::FGarbageCollectionHandle2Value ScriptInterfaceGarbageCollectionHandle2Address;

	FScriptInterfaceMapping::FKey2GarbageCollectionHandle ScriptInterfaceAddress2GarbageCollectionHandle;

	FSoftClassPtrMapping::FGarbageCollectionHandle2Value SoftClassPtrGarbageCollectionHandle2Address;

	FSoftClassPtrMapping::FAddress2GarbageCollectionHandle SoftClassPtrAddress2GarbageCollectionHandle;
};

#include "FMultiRegistry.inl"
