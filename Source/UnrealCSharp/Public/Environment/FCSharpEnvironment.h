#pragma once

#include "Domain/FDomain.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FMultiRegistry.h"
#include "Registry/FReferenceRegistry.h"
#include "Registry/FObjectRegistry.h"
#include "Registry/FStructRegistry.h"
#include "Registry/FDynamicRegistry.h"
#include "Template/TIsUObject.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsScriptStruct.inl"
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

	bool Bind(MonoObject* InMonoObject, const FName& InStructName) const;

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* AddClassDescriptor(const FDomain* InDomain, UStruct* InStruct) const;

	void RemoveClassDescriptor(const UStruct* InStruct) const;

	FFunctionDescriptor* GetFunctionDescriptor(const UStruct* InStruct, const FName& InFunctionName) const;

	FFunctionDescriptor* GetFunctionDescriptor(uint32 InFunctionHash) const;

	void AddFunctionDescriptor(uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor) const;

	void AddFunctionHash(uint32 InFunctionHash, FClassDescriptor* InClassDescriptor, const FName& InFunctionName) const;

	void RemoveFunctionDescriptor(uint32 InFunctionHash) const;

	FPropertyDescriptor* GetPropertyDescriptor(uint32 InPropertyHash) const;

	void AddPropertyDescriptor(uint32 InPropertyHash, FPropertyDescriptor* InPropertyDescriptor) const;

	void RemovePropertyDescriptor(uint32 InPropertyHash) const;

public:
	template <typename T>
	void* GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct) const;

	template <typename T, typename U>
	auto GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T, typename U>
	auto GetAddress(const MonoObject* InMonoObject) const;

	bool AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const;

	MonoObject* GetObject(const UObject* InObject) const;

	template <typename T = UObject>
	auto GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T = UObject>
	auto GetObject(const MonoObject* InMonoObject) const;

	bool RemoveObjectReference(const UObject* InObject) const;

	bool RemoveObjectReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	bool AddStructReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject,
	                        bool bNeedFree = true) const;

	bool AddStructReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
	                        const void* InStruct, MonoObject* InMonoObject) const;

	MonoObject* GetObject(UScriptStruct* InScriptStruct, const void* InStruct) const;

	void* GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	void* GetStruct(const MonoObject* InMonoObject) const;

	bool RemoveStructReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(const UObject* InObject) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(void* InAddress, const FProperty* InProperty) const;

public:
	template <typename T>
	auto GetContainer(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetContainerObject(void* InAddress) const;

	template <typename T>
	auto AddContainerReference(void* InAddress, T* InValue, MonoObject* InMonoObject) const;

	template <typename T>
	auto AddContainerReference(const FGarbageCollectionHandle& InOwner, void* InAddress, T* InValue,
	                           MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveContainerReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

public:
	template <typename T>
	auto GetDelegate(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetDelegateObject(void* InAddress) const;

	template <typename T>
	auto AddDelegateReference(void* InAddress, T* InValue, MonoObject* InMonoObject) const;

	template <typename T>
	auto AddDelegateReference(const FGarbageCollectionHandle& InOwner, void* InAddress, T* InValue,
	                          MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveDelegateReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

private:
	template <typename T, typename U>
	class TGetAddress
	{
	};

	template <typename T>
	class TGetAddress<UObject, T>
	{
	public:
		T* operator()(const FCSharpEnvironment* InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

		T* operator()(const FCSharpEnvironment* InEnvironment, const MonoObject* InMonoObject) const;
	};

	template <typename T>
	class TGetAddress<UScriptStruct, T>
	{
	public:
		T* operator()(const FCSharpEnvironment* InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

		T* operator()(const FCSharpEnvironment* InEnvironment, const MonoObject* InMonoObject) const;
	};

public:
	template <typename T>
	auto GetMulti(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetMulti(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetMultiObject(void* InAddress) const;

	template <typename T>
	auto AddMultiReference(MonoObject* InMonoObject, void* InValue, bool bNeedFree = true) const;

	template <typename T>
	auto RemoveMultiReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

public:
	MonoObject* GetBinding(void* InObject) const;

	template <typename T>
	auto GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetBinding(const MonoObject* InMonoObject) const;

	template <typename T>
	auto AddBindingReference(MonoObject* InMonoObject, const T* InObject) const;

	template <typename T>
	auto AddBindingReference(const FGarbageCollectionHandle& InOwner, MonoObject* InMonoObject,
	                         const T* InObject) const;

	bool RemoveBindingReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

public:
	template <typename T, typename Enable = void>
	class TGetObject
	{
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsUObject<T>::Value, T>>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return InEnvironment.GetObject<T>(InGarbageCollectionHandle);
		}

		T* operator()(const FCSharpEnvironment& InEnvironment, const MonoObject* InMonoObject) const
		{
			return InEnvironment.GetObject<T>(InMonoObject);
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsUStruct<T>::Value, T>>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return static_cast<T*>(InEnvironment.GetStruct(InGarbageCollectionHandle));
		}

		T* operator()(const FCSharpEnvironment& InEnvironment, const MonoObject* InMonoObject) const
		{
			return static_cast<T*>(InEnvironment.GetStruct(InMonoObject));
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsScriptStruct<T>::Value, T>>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return static_cast<T*>(InEnvironment.GetStruct(InGarbageCollectionHandle));
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<!(TIsUObject<T>::Value ||
		                                     TIsUStruct<T>::Value ||
		                                     TIsScriptStruct<T>::Value),
	                                     T>>
	{
	public:
		T* operator()(const FCSharpEnvironment& InEnvironment,
		              const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return InEnvironment.GetBinding<T>(InGarbageCollectionHandle);
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
	class FCSharpBind* CSharpBind;

	FClassRegistry* ClassRegistry;

	FReferenceRegistry* ReferenceRegistry;

	FObjectRegistry* ObjectRegistry;

	FStructRegistry* StructRegistry;

	class FContainerRegistry* ContainerRegistry;

	class FDelegateRegistry* DelegateRegistry;

	FMultiRegistry* MultiRegistry;

	FDynamicRegistry* DynamicRegistry;

	class FBindingRegistry* BindingRegistry;
};

#include "FCSharpEnvironment.inl"
