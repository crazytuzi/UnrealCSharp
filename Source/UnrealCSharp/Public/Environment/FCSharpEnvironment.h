#pragma once

#include "Domain/FDomain.h"
#include "Registry/FDynamicRegistry.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FMultiRegistry.h"
#include "Registry/FStringRegistry.h"
#include "Registry/FReferenceRegistry.h"
#include "Registry/FObjectRegistry.h"
#include "Registry/FStructRegistry.h"
#include "Template/TIsUObject.inl"
#include "Template/TIsUStruct.inl"
#include "Template/TIsScriptStruct.inl"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "UEVersion.h"

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
	template <auto IsNeedMonoClass>
	auto Bind(UStruct* InStruct) const;

	MonoObject* Bind(UObject* Object) const;

	MonoObject* Bind(const UObject* Object) const;

	MonoObject* Bind(UClass* Class) const;

	template <auto IsNeedMonoClass>
	auto Bind(UObject* Object) const;

	bool Bind(MonoObject* InMonoObject, const FName& InStructName) const;

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* AddClassDescriptor(UStruct* InStruct) const;

	void RemoveClassDescriptor(const UStruct* InStruct) const;

	FFunctionDescriptor* GetOrAddFunctionDescriptor(const UStruct* InStruct, const FString& InFunctionName) const;

	FFunctionDescriptor* GetFunctionDescriptor(uint32 InFunctionHash) const;

	FFunctionDescriptor* GetOrAddFunctionDescriptor(uint32 InFunctionHash) const;

	void AddFunctionDescriptor(uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor) const;

	void AddFunctionHash(uint32 InFunctionHash, FClassDescriptor* InClassDescriptor,
	                     const FString& InFunctionName) const;

	void RemoveFunctionDescriptor(uint32 InFunctionHash) const;

	FPropertyDescriptor* GetOrAddPropertyDescriptor(uint32 InPropertyHash) const;

	void AddPropertyDescriptor(uint32 InPropertyHash, FPropertyDescriptor* InPropertyDescriptor) const;

	void AddPropertyHash(uint32 InPropertyHash, FClassDescriptor* InClassDescriptor,
	                     const FString& InPropertyName) const;

	void RemovePropertyDescriptor(uint32 InPropertyHash) const;

public:
	template <typename T>
	auto GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle, UStruct*& InStruct) const -> void*;

	template <typename T, typename U>
	auto GetAddress(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	bool AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const;

	MonoObject* GetObject(const UObject* InObject) const;

	template <typename T = UObject>
	auto GetObject(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	bool RemoveObjectReference(const UObject* InObject) const;

	bool RemoveObjectReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <auto IsNeedFree>
	auto AddStructReference(UScriptStruct* InScriptStruct, const void* InStruct, MonoObject* InMonoObject) const;

	bool AddStructReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
	                        const void* InStruct, MonoObject* InMonoObject) const;

	MonoObject* GetObject(UScriptStruct* InScriptStruct, const void* InStruct) const;

	void* GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	bool RemoveStructReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(const UObject* InObject) const;

	FGarbageCollectionHandle GetGarbageCollectionHandle(void* InAddress, const FProperty* InProperty) const;

public:
	template <typename T>
	auto GetContainer(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetContainerObject(void* InAddress) const;

	template <typename T>
	auto AddContainerReference(T* InValue, MonoObject* InMonoObject) const;

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
	auto AddDelegateReference(T* InValue, MonoObject* InMonoObject) const;

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
		auto operator()(const FCSharpEnvironment* InEnvironment,
		                const FGarbageCollectionHandle& InGarbageCollectionHandle) const -> T*;
	};

	template <typename T>
	class TGetAddress<UScriptStruct, T>
	{
	public:
		auto operator()(const FCSharpEnvironment* InEnvironment,
		                const FGarbageCollectionHandle& InGarbageCollectionHandle) const -> T*;
	};

public:
	template <typename T>
	auto GetMulti(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetMultiObject(void* InAddress) const;

	template <typename T, auto IsNeedFree, auto IsMember>
	auto AddMultiReference(MonoObject* InMonoObject, void* InValue) const;

	template <typename T>
	auto RemoveMultiReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

public:
	template <typename T>
	auto GetString(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetStringObject(void* InAddress) const;

	template <typename T, auto IsNeedFree, auto IsMember>
	auto AddStringReference(MonoObject* InMonoObject, void* InValue) const;

	template <typename T>
	auto RemoveStringReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

public:
	MonoObject* GetBinding(void* InObject) const;

	template <typename T>
	auto GetBinding(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T, auto IsNeedFree>
	auto AddBindingReference(MonoObject* InMonoObject, const T* InObject) const;

	template <typename T>
	auto AddBindingReference(const FGarbageCollectionHandle& InOwner, MonoObject* InMonoObject,
	                         const T* InObject) const;

	bool RemoveBindingReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

#if UE_F_OPTIONAL_PROPERTY
public:
	class FOptionalHelper* GetOptional(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;

	template <typename T>
	auto GetOptionalObject(void* InAddress) const;

	template <typename T, auto IsMember>
	auto AddOptionalReference(void* InAddress, T* InValue, MonoObject* InMonoObject) const;

	bool RemoveOptionalReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const;
#endif

public:
	template <typename T, typename Enable = void>
	class TGetObject
	{
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsUObject<T>::Value, T>>
	{
	public:
		auto operator()(const FCSharpEnvironment& InEnvironment,
		                const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return InEnvironment.GetObject<T>(InGarbageCollectionHandle);
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsUStruct<T>::Value, T>>
	{
	public:
		auto operator()(const FCSharpEnvironment& InEnvironment,
		                const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return static_cast<T*>(InEnvironment.GetStruct(InGarbageCollectionHandle));
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsScriptStruct<T>::Value, T>>
	{
	public:
		auto operator()(const FCSharpEnvironment& InEnvironment,
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
		auto operator()(const FCSharpEnvironment& InEnvironment,
		                const FGarbageCollectionHandle& InGarbageCollectionHandle) const
		{
			return InEnvironment.GetBinding<T>(InGarbageCollectionHandle);
		}
	};

public:
	bool AddReference(const FGarbageCollectionHandle& InOwner, class FReference* InReference) const;

	bool RemoveReference(const FGarbageCollectionHandle& InOwner) const;

public:
	template <typename T>
	auto GetRegistry();

	class FCSharpBind* GetBind() const;

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
	FDynamicRegistry* DynamicRegistry;

	class FCSharpBind* CSharpBind;

	FClassRegistry* ClassRegistry;

	FReferenceRegistry* ReferenceRegistry;

	FObjectRegistry* ObjectRegistry;

	FStructRegistry* StructRegistry;

	class FContainerRegistry* ContainerRegistry;

	class FDelegateRegistry* DelegateRegistry;

	FMultiRegistry* MultiRegistry;

	FStringRegistry* StringRegistry;

	class FBindingRegistry* BindingRegistry;

#if UE_F_OPTIONAL_PROPERTY
	class FOptionalRegistry* OptionalRegistry;
#endif
};

#include "FCSharpEnvironment.inl"
