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
	void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index);

	void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index);

	void OnUObjectArrayShutdown();

	void OnUnrealCSharpModuleActive();

	void OnUnrealCSharpModuleInActive();

	void OnAsyncLoadingFlushUpdate();

public:
	template <auto IsNeedOverride>
	auto Bind(UStruct* InStruct) const;

	IManagedObject Bind(UObject* Object) const;

	IManagedObject Bind(const UObject* Object) const;

	IManagedObject Bind(UClass* Class) const;

	template <auto IsNeedOverride>
	auto Bind(UObject* Object) const;

	bool Bind(const IManagedObject InManagedObject, const FName& InStructName) const;

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* AddClassDescriptor(UStruct* InStruct) const;

	void RemoveClassDescriptor(const UStruct* InStruct) const;

	template <typename T>
	auto GetFunctionDescriptor(const uint32 InFunctionHash) const -> T*;

	template <typename T>
	auto GetOrAddFunctionDescriptor(const uint32 InFunctionHash) const -> T*;

	template <typename T, typename... Args>
	auto AddFunctionHash(Args&&... InArgs) const -> void;

	void RemoveFunctionDescriptor(uint32 InFunctionHash) const;

	FPropertyDescriptor* GetOrAddPropertyDescriptor(uint32 InPropertyHash) const;

	void AddPropertyHash(uint32 InPropertyHash, FClassDescriptor* InClassDescriptor, FProperty* InProperty) const;

	void RemovePropertyDescriptor(uint32 InPropertyHash) const;

public:
	template <typename T>
	auto GetAddress(const IManagedHandle InManagedHandle, UStruct*& InStruct) const -> void*;

	template <typename T, typename U>
	auto GetAddress(const IManagedHandle InManagedHandle) const;

	bool AddObjectReference(const FClassReflection* InClass, UObject* InObject, IManagedHandle InManagedHandle) const;

	IManagedHandle GetObject(const UObject* InObject) const;

	template <typename T = UObject>
	auto GetObject(const IManagedHandle InManagedHandle) const;

	bool RemoveObjectReference(const UObject* InObject) const;

	bool RemoveObjectReference(const IManagedHandle InManagedHandle) const;

	template <auto IsNeedFree>
	auto AddStructReference(UScriptStruct* InScriptStruct, const void* InStruct,
	                        const IManagedHandle InManagedHandle) const;

	bool AddStructReference(const IManagedHandle InOwner, UScriptStruct* InScriptStruct,
	                        const void* InStruct, const IManagedHandle InManagedHandle) const;

	IManagedHandle GetObject(UScriptStruct* InScriptStruct, const void* InStruct) const;

	template <typename T = void>
	auto GetStruct(const IManagedHandle InManagedHandle) const -> T*;

	bool RemoveStructReference(const IManagedHandle InManagedHandle) const;

	IManagedHandle GeManagedHandle(const UObject* InObject) const;

	IManagedHandle GeManagedHandle(void* InAddress, const FProperty* InProperty) const;

public:
	template <typename T>
	auto GetContainer(const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto GetContainerObject(void* InAddress) const;

	template <typename T>
	auto AddContainerReference(T* InValue, FClassReflection* InClass, const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto AddContainerReference(const IManagedHandle InOwner, void* InAddress, T* InValue,
	                           FClassReflection* InClass, const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto RemoveContainerReference(const IManagedHandle InManagedHandle) const;

public:
	template <typename T>
	auto GetDelegate(const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto GetDelegateObject(void* InAddress) const;

	template <typename T>
	auto AddDelegateReference(T* InValue, FClassReflection* InClass, const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto AddDelegateReference(const IManagedHandle InOwner, void* InAddress, T* InValue,
	                          FClassReflection* InClass, const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto RemoveDelegateReference(const IManagedHandle InManagedHandle) const;

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
		                const IManagedHandle InManagedHandle) const -> T*;
	};

	template <typename T>
	class TGetAddress<UScriptStruct, T>
	{
	public:
		auto operator()(const FCSharpEnvironment* InEnvironment,
		                const IManagedHandle InManagedHandle) const -> T*;
	};

public:
	template <typename T>
	auto GetMulti(const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto GetMultiObject(void* InAddress) const;

	template <typename T, auto IsNeedFree, auto IsMember>
	auto AddMultiReference(FClassReflection* InClass, const IManagedHandle InManagedHandle, void* InValue) const;

	template <typename T>
	auto RemoveMultiReference(const IManagedHandle InManagedHandle) const;

public:
	template <typename T>
	auto GetString(const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto GetStringObject(void* InAddress) const;

	template <typename T, auto IsNeedFree, auto IsMember>
	auto AddStringReference(FClassReflection* InClass, const IManagedHandle InManagedHandle, void* InValue) const;

	template <typename T>
	auto RemoveStringReference(const IManagedHandle InManagedHandle) const;

public:
	IManagedHandle GetBinding(void* InObject) const;

	template <typename T>
	auto GetBinding(const IManagedHandle InManagedHandle) const;

	template <typename T, auto IsNeedFree>
	auto AddBindingReference(FClassReflection* InClass, const IManagedHandle InManagedHandle, const T* InObject) const;

	template <typename T>
	auto AddBindingReference(const IManagedHandle InOwner, FClassReflection* InClass,
	                         const IManagedHandle InManagedHandle, const T* InObject) const;

	bool RemoveBindingReference(const IManagedHandle InManagedHandle) const;

#if UE_F_OPTIONAL_PROPERTY
public:
	class FOptionalHelper* GetOptional(const IManagedHandle InManagedHandle) const;

	template <typename T>
	auto GetOptionalObject(void* InAddress) const;

	template <typename T, auto IsMember>
	auto AddOptionalReference(void* InAddress, T* InValue, FClassReflection* InClass,
	                          const IManagedHandle InManagedHandle) const;

	bool RemoveOptionalReference(const IManagedHandle InManagedHandle) const;
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
		                const IManagedHandle InManagedHandle) const
		{
			return InEnvironment.GetObject<T>(InManagedHandle);
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsUStruct<T>::Value, T>>
	{
	public:
		auto operator()(const FCSharpEnvironment& InEnvironment,
		                const IManagedHandle InManagedHandle) const
		{
			return InEnvironment.GetStruct<T>(InManagedHandle);
		}
	};

	template <typename T>
	class TGetObject<T, std::enable_if_t<TIsScriptStruct<T>::Value, T>>
	{
	public:
		auto operator()(const FCSharpEnvironment& InEnvironment,
		                const IManagedHandle InManagedHandle) const
		{
			return InEnvironment.GetStruct<T>(InManagedHandle);
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
		                const IManagedHandle InManagedHandle) const
		{
			return InEnvironment.GetBinding<T>(InManagedHandle);
		}
	};

public:
	bool AddReference(const IManagedHandle InOwner, class FReference* InReference) const;

	bool RemoveReference(const IManagedHandle InOwner) const;

	bool AddReference(UObject* InObject) const;

	bool RemoveReference(UObject* InObject) const;

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
