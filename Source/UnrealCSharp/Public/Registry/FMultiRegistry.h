#pragma once

#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTSubclassOf.inl"
#include "TValue.inl"
#include "TValueMapping.inl"

class FMultiRegistry
{
public:
	template <typename T, template<typename...> class IsType>
	struct TMultiAddress : TValue<T>
	{
		template <typename U>
		struct TIsType
		{
			enum { value = IsType<U>::Value };
		};

		TMultiAddress(T InValue, const bool InNeedFree):
			TValue<T>(InValue),
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

	template <typename Key, typename Value>
	struct TMultiValueMapping : TValueMapping<Key, Value>
	{
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

	template <typename T, typename P, P, typename Q, Q, typename R, R>
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
	FSubclassOfMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2SubclassOfAddress;

	FSubclassOfMapping::FKey2GarbageCollectionHandle SubclassOfAddress2GarbageCollectionHandle;

	FSubclassOfMapping::FMonoObject2Value MonoObject2SubclassOfAddress;

	FWeakObjectPtrMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2WeakObjectPtrAddress;

	FWeakObjectPtrMapping::FKey2GarbageCollectionHandle WeakObjectPtrAddress2GarbageCollectionHandle;

	FWeakObjectPtrMapping::FMonoObject2Value MonoObject2WeakObjectPtrAddress;

	FLazyObjectPtrMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2LazyObjectPtrAddress;

	FLazyObjectPtrMapping::FKey2GarbageCollectionHandle LazyObjectPtrAddress2GarbageCollectionHandle;

	FLazyObjectPtrMapping::FMonoObject2Value MonoObject2LazyObjectPtrAddress;

	FSoftObjectPtrMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2SoftObjectPtrAddress;

	FSoftObjectPtrMapping::FKey2GarbageCollectionHandle SoftObjectPtrAddress2GarbageCollectionHandle;

	FSoftObjectPtrMapping::FMonoObject2Value MonoObject2SoftObjectPtrAddress;

	FScriptInterfaceMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2ScriptInterfaceAddress;

	FScriptInterfaceMapping::FKey2GarbageCollectionHandle ScriptInterfaceAddress2GarbageCollectionHandle;

	FScriptInterfaceMapping::FMonoObject2Value MonoObject2ScriptInterfaceAddress;

	FSoftClassPtrMapping::FGarbageCollectionHandle2Value GarbageCollectionHandle2SoftClassPtrAddress;

	FSoftClassPtrMapping::FKey2GarbageCollectionHandle SoftClassPtrAddress2GarbageCollectionHandle;

	FSoftClassPtrMapping::FMonoObject2Value MonoObject2SoftClassPtrAddress;
};

#include "FMultiRegistry.inl"
