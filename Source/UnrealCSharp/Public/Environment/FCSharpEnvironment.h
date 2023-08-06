#pragma once

#include "Domain/FDomain.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FContainerRegistry.h"
#include "Registry/FMultiRegistry.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FReferenceRegistry.h"
#include "Registry/FObjectRegistry.h"
#include "Registry/FStructRegistry.h"
#include "Registry/FMixinRegistry.h"
#include "Registry/FBindingRegistry.h"
#include "Template/TIsUObject.inl"
#include "Template/TIsUStruct.inl"
#include "GarbageCollection/FGarbageCollectionHandle.h"

class UNREALCSHARP_API FCSharpEnvironment
{
public:
	FCSharpEnvironment();

	~FCSharpEnvironment();

public:
	void Initialize();

	void Deinitialize();

public:
	static FCSharpEnvironment& GetEnvironment();

public:
	FDomain* GetDomain() const;

public:
	void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index);

	void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index);

	void OnUObjectArrayShutdown();

	void OnUnrealCSharpModuleActive();

	void OnUnrealCSharpModuleInActive();

	void OnAsyncLoadingFlushUpdate();

public:
	MonoObject* Bind(UObject* Object) const;

	bool Bind(UObject* Object, bool bNeedMonoClass) const;

	bool Bind(UStruct* InStruct, bool bNeedMonoClass) const;

	bool Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	          MonoReflectionType* InValueReflectionType) const;

	bool Bind(MonoObject* InMonoObject, const FName& InStructName) const;

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* NewClassDescriptor(const FDomain* InDomain, UStruct* InStruct) const;

	void DeleteClassDescriptor(const UStruct* InStruct) const;

	FFunctionDescriptor* GetFunctionDescriptor(const UStruct* InStruct, const FName& InFunctionName) const;

	FFunctionDescriptor* GetFunctionDescriptor(const FName& InClassName, const FName& InFunctionName) const;

	FPropertyDescriptor* GetPropertyDescriptor(const UStruct* InStruct, const FName& InPropertyName) const;

public:
	template <typename T>
	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct) const;

	template <typename T, typename U>
	auto GetAddress(const MonoObject* InMonoObject) const;

	bool AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const;

	MonoObject* GetObject(const UObject* InObject) const;

	template <typename T = UObject>
	auto GetObject(const MonoObject* InMonoObject) const;

	bool RemoveObjectReference(const UObject* InObject) const;

	bool RemoveObjectReference(const MonoObject* InMonoObject) const;

	bool AddStructReference(UScriptStruct* InScriptStruct, const void* InOwner, const void* InStruct,
	                        MonoObject* InMonoObject, bool bNeedFree = true) const;

	MonoObject* GetObject(const void* InOwner, const void* InStruct) const;

	void* GetStruct(const MonoObject* InMonoObject) const;

	bool RemoveStructReference(const MonoObject* InMonoObject) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(void* InAddress, int32 InOffset) const;

public:
	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetContainer(const void* InAddress) const;

	MonoObject* GetContainerObject(const void* InAddress) const;

	bool AddContainerReference(void* InContainer, MonoObject* InMonoObject, void* InAddress = nullptr) const;

	bool AddContainerReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
	                           MonoObject* InMonoObject) const;

	bool RemoveContainerReference(const MonoObject* InMonoObject) const;

public:
	template <typename T>
	auto GetDelegate(const MonoObject* InMonoObject) const;

	MonoObject* GetDelegateObject(const void* InAddress) const;

	bool AddDelegateReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject) const;

	bool AddDelegateReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
	                          MonoObject* InMonoObject) const;

	bool RemoveDelegateReference(const MonoObject* InMonoObject) const;

private:
	template <typename T, typename U>
	class TGetAddress
	{
	};

	template <typename T>
	class TGetAddress<UObject, T>
	{
	public:
		T* operator()(const FCSharpEnvironment* InEnvironment, const MonoObject* InMonoObject) const;
	};

	template <typename T>
	class TGetAddress<UScriptStruct, T>
	{
	public:
		T* operator()(const FCSharpEnvironment* InEnvironment, const MonoObject* InMonoObject) const;
	};

public:
	template <typename T>
	auto GetMulti(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetMultiObject(const void* InAddress) const;

	template <typename T>
	auto AddMultiReference(MonoObject* InMonoObject, void* InValue, bool bNeedFree = true) const;

	template <typename T>
	auto RemoveMultiReference(const MonoObject* InMonoObject) const;

public:
	MonoObject* GetBinding(const void* InObject) const;

	template <typename T>
	auto GetBinding(const MonoObject* InMonoObject) const;

	bool AddBindingReference(MonoObject* InMonoObject, const void* InObject, bool bNeedFree = true) const;

	bool RemoveBindingReference(const MonoObject* InMonoObject) const;

public:
	template <typename T, typename Enable = void>
	class TGetObject
	{
	};

	template <typename T>
	class TGetObject<T, typename TEnableIf<TIsUObject<T>::Value, T>::Type>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment, const MonoObject* InMonoObject) const
		{
			return InEnvironment.GetObject<T>(InMonoObject);
		}
	};

	template <typename T>
	class TGetObject<T, typename TEnableIf<TIsUStruct<T>::Value, T>::Type>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment, const MonoObject* InMonoObject) const
		{
			return static_cast<T*>(InEnvironment.GetStruct(InMonoObject));
		}
	};

	template <typename T>
	class TGetObject<T, typename TEnableIf<TNot<TOr<TIsUObject<T>, TIsUStruct<T>>>::Value, T>::Type>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment, const MonoObject* InMonoObject) const
		{
			return InEnvironment.GetBinding<T>(InMonoObject);
		}
	};

public:
	bool AddReference(const FGarbageCollectionHandle& InOwner, class FReference* InReference) const;

	bool RemoveReference(const FGarbageCollectionHandle& InOwner) const;

private:
	static FCSharpEnvironment Environment;

	FDomain* Domain;

private:
	FDelegateHandle OnUnrealCSharpModuleActiveDelegateHandle;

	FDelegateHandle OnUnrealCSharpModuleInActiveDelegateHandle;

	FDelegateHandle OnAsyncLoadingFlushUpdateHandle;

private:
	FCriticalSection CriticalSection;

	TArray<FWeakObjectPtr> AsyncLoadingObjectArray;

private:
	FClassRegistry* ClassRegistry;

	FReferenceRegistry* ReferenceRegistry;

	FObjectRegistry* ObjectRegistry;

	FStructRegistry* StructRegistry;

	FContainerRegistry* ContainerRegistry;

	FDelegateRegistry* DelegateRegistry;

	FMultiRegistry* MultiRegistry;

	FMixinRegistry* MixinRegistry;

	FBindingRegistry* BindingRegistry;
};

#include "FCSharpEnvironment.inl"
