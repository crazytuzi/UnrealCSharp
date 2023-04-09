#pragma once

#include "Domain/FMonoDomain.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FContainerRegistry.h"
#include "Registry/FCSharpBind.h"
#include "Registry/FMultiRegistry.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FReferenceRegistry.h"
#include "Registry/FObjectRegistry.h"
#include "Registry/FStructRegistry.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"

class FCSharpEnvironment
{
public:
	FCSharpEnvironment();

	~FCSharpEnvironment();

public:
	void Initialize();

	void Deinitialize();

public:
	static FCSharpEnvironment* GetEnvironment();

public:
	FMonoDomain* GetDomain() const;

public:
	void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index);

	void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index);

	void OnUObjectArrayShutdown();

	void OnUnrealCSharpModuleInActive();

	void OnAsyncLoadingFlushUpdate();

public:
	MonoObject* Bind(UObject* Object) const;

	bool Bind(UObject* Object, bool bNeedMonoClass) const;

	bool Bind(UStruct* InStruct, bool bNeedMonoClass) const;

	template <typename T>
	auto Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType) const;

	bool Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	          MonoReflectionType* InValueReflectionType) const;

	bool Bind(MonoObject* InMonoObject, const FName& InStructName) const;

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* NewClassDescriptor(const FMonoDomain* InMonoDomain, UStruct* InStruct) const;

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

	bool RemoveStructReference(const void* InOwner, const void* InStruct) const;

	bool RemoveStructReference(const MonoObject* InMonoObject) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(void* InAddress, int32 InOffset) const;

public:
	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetContainer(const void* InAddress) const;

	MonoObject* GetContainerObject(const void* InAddress) const;

	bool AddContainerReference(void* InContainer, MonoObject* InMonoObject) const;

	bool AddContainerReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InContainer,
	                           MonoObject* InMonoObject) const;

	bool RemoveContainerReference(const MonoObject* InMonoObject) const;

	bool RemoveContainerReference(const void* InAddress) const;

public:
	template <typename T>
	auto GetDelegate(const MonoObject* InMonoObject) const;

	MonoObject* GetDelegateObject(const void* InAddress) const;

	bool AddDelegateReference(const FGarbageCollectionHandle& InOwner, void* InAddress, void* InDelegate,
	                          MonoObject* InMonoObject) const;

	bool RemoveDelegateReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

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
	auto AddMultiReference(MonoObject* InMonoObject, const T& InValue) const;

	template <typename T>
	auto AddMultiReference(void* InAddress, MonoObject* InMonoObject, const T& InValue) const;

	template <typename T>
	auto RemoveMultiReference(const MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveMultiReference(const void* InAddress) const;

public:
	bool AddReference(const FGarbageCollectionHandle& InOwner, class FReference* InReference) const;

	bool RemoveReference(const FGarbageCollectionHandle& InOwner) const;

private:
	static FCSharpEnvironment* Environment;

	FMonoDomain* Domain;

private:
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
};

#include "FCSharpEnvironment.inl"
