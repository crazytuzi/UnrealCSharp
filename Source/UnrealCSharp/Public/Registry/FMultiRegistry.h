#pragma once

#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTSubclassOf.inl"
#include "TAddress.inl"
#include "TValueMapping.inl"

class FMultiRegistry
{
public:
	template <typename T, template<typename...> class IsType>
	struct TMultiAddress : TTypeAddress<T, IsType>
	{
		TMultiAddress(void* InAddress, T InValue, const bool InNeedFree):
			TTypeAddress<T, IsType>(InAddress, InValue),
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

	template <typename T, typename U = T>
	struct TMultiRegistry
	{
	};

	template <typename R, R, typename U, typename V, typename P, P, typename Q, Q>
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
	TValueMapping<void*, FSubclassOfAddress>::GarbageCollectionHandle2Value GarbageCollectionHandle2SubclassOfAddress;

	TValueMapping<void*, FSubclassOfAddress>::Value2GarbageCollectionHandle SubclassOfAddress2GarbageCollectionHandle;

	TValueMapping<void*, FSubclassOfAddress>::MonoObject2Value MonoObject2SubclassOfAddress;

	TValueMapping<void*, FWeakObjectPtrAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2WeakObjectPtrAddress;

	TValueMapping<void*, FWeakObjectPtrAddress>::Value2GarbageCollectionHandle
	WeakObjectPtrAddress2GarbageCollectionHandle;

	TValueMapping<void*, FWeakObjectPtrAddress>::MonoObject2Value MonoObject2WeakObjectPtrAddress;

	TValueMapping<void*, FLazyObjectPtrAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2LazyObjectPtrAddress;

	TValueMapping<void*, FLazyObjectPtrAddress>::Value2GarbageCollectionHandle
	LazyObjectPtrAddress2GarbageCollectionHandle;

	TValueMapping<void*, FLazyObjectPtrAddress>::MonoObject2Value MonoObject2LazyObjectPtrAddress;

	TValueMapping<void*, FSoftObjectPtrAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2SoftObjectPtrAddress;

	TValueMapping<void*, FSoftObjectPtrAddress>::Value2GarbageCollectionHandle
	SoftObjectPtrAddress2GarbageCollectionHandle;

	TValueMapping<void*, FSoftObjectPtrAddress>::MonoObject2Value MonoObject2SoftObjectPtrAddress;

	TValueMapping<void*, FScriptInterfaceAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2ScriptInterfaceAddress;

	TValueMapping<void*, FScriptInterfaceAddress>::Value2GarbageCollectionHandle
	ScriptInterfaceAddress2GarbageCollectionHandle;

	TValueMapping<void*, FScriptInterfaceAddress>::MonoObject2Value MonoObject2ScriptInterfaceAddress;

	TValueMapping<void*, FSoftClassPtrAddress>::GarbageCollectionHandle2Value
	GarbageCollectionHandle2SoftClassPtrAddress;

	TValueMapping<void*, FSoftClassPtrAddress>::Value2GarbageCollectionHandle
	SoftClassPtrAddress2GarbageCollectionHandle;

	TValueMapping<void*, FSoftClassPtrAddress>::MonoObject2Value MonoObject2SoftClassPtrAddress;
};

#include "FMultiRegistry.inl"
