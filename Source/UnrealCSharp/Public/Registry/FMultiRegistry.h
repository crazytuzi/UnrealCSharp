#pragma once

#include "GarbageCollection/TGarbageCollectionHandleMapping.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTSubclassOf.inl"

class FMultiRegistry
{
public:
	template <typename T, template<typename...> class IsType>
	struct TMultiAddress
	{
		typedef T Type;

		void* Address;

		Type* Value;

		bool bNeedFree;

		template <typename U>
		struct TIsType
		{
			enum { Value = IsType<U>::Value };
		};
	};

	typedef TMultiAddress<TSubclassOf<UObject>, TIsTSubclassOf> FSubclassOfAddress;

	typedef TMultiAddress<TWeakObjectPtr<UObject>, TIsTWeakObjectPtr> FWeakObjectPtrAddress;

	typedef TMultiAddress<TLazyObjectPtr<UObject>, TIsTLazyObjectPtr> FLazyObjectPtrAddress;

	typedef TMultiAddress<TSoftObjectPtr<UObject>, TIsTSoftObjectPtr> FSoftObjectPtrAddress;

	typedef TMultiAddress<TScriptInterface<IInterface>, TIsTScriptInterface> FScriptInterfaceAddress;

	typedef TMultiAddress<TSoftClassPtr<UObject>, TIsTSoftClassPtr> FSoftClassPtrAddress;

	template <typename T, typename U = T>
	struct TMultiRegistry
	{
	};

	template <typename R, R, typename U, typename S, S>
	struct TMultiRegistryImplementation
	{
	};

	template <typename T>
	struct TMultiMapping
	{
		typedef T Key;

		typedef TGarbageCollectionHandleMapping<T> GarbageCollectionHandle2Address;

		typedef typename TGarbageCollectionHandleMapping<Key>::Key Value;

		typedef TMap<void*, Value> Address2GarbageCollectionHandle;
	};

public:
	FMultiRegistry();

	~FMultiRegistry();

public:
	void Initialize();

	void Deinitialize();

private:
	TMultiMapping<FSubclassOfAddress>::GarbageCollectionHandle2Address GarbageCollectionHandle2SubclassOfAddress;

	TMultiMapping<FSubclassOfAddress>::Address2GarbageCollectionHandle SubclassOfAddress2GarbageCollectionHandle;

	TMultiMapping<FWeakObjectPtrAddress>::GarbageCollectionHandle2Address GarbageCollectionHandle2WeakObjectPtrAddress;

	TMultiMapping<FWeakObjectPtrAddress>::Address2GarbageCollectionHandle WeakObjectPtrAddress2GarbageCollectionHandle;

	TMultiMapping<FLazyObjectPtrAddress>::GarbageCollectionHandle2Address GarbageCollectionHandle2LazyObjectPtrAddress;

	TMultiMapping<FLazyObjectPtrAddress>::Address2GarbageCollectionHandle LazyObjectPtrAddress2GarbageCollectionHandle;

	TMultiMapping<FSoftObjectPtrAddress>::GarbageCollectionHandle2Address GarbageCollectionHandle2SoftObjectPtrAddress;

	TMultiMapping<FSoftObjectPtrAddress>::Address2GarbageCollectionHandle SoftObjectPtrAddress2GarbageCollectionHandle;

	TMultiMapping<FScriptInterfaceAddress>::GarbageCollectionHandle2Address
	GarbageCollectionHandle2ScriptInterfaceAddress;

	TMultiMapping<FScriptInterfaceAddress>::Address2GarbageCollectionHandle
	ScriptInterfaceAddress2GarbageCollectionHandle;

	TMultiMapping<FSoftClassPtrAddress>::GarbageCollectionHandle2Address GarbageCollectionHandle2SoftClassPtrAddress;

	TMultiMapping<FSoftClassPtrAddress>::Address2GarbageCollectionHandle SoftClassPtrAddress2GarbageCollectionHandle;
};

#include "FMultiRegistry.inl"
