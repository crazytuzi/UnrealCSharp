#pragma once

#include "Domain/FMonoDomain.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FContainerRegistry.h"
#include "Registry/FCSharpBind.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FObjectRegistry.h"
#include "Registry/FStructRegistry.h"

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

public:
	bool Bind(UObject* Object) const;

	bool Bind(UStruct* InStruct, bool bNeedMonoClass = true) const;

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
	template<typename T>
	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct) const;

	template <typename T, typename U>
	U* GetAddress(const MonoObject* InMonoObject) const;

	bool AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const;

	MonoObject* GetObject(const UObject* InObject) const;

	UObject* GetObject(const MonoObject* InMonoObject) const;

	bool RemoveObjectReference(const UObject* InObject) const;

	bool RemoveObjectReference(const MonoObject* InMonoObject) const;

	bool AddStructReference(UScriptStruct* InScriptStruct, void* InStruct, MonoObject* InMonoObject,
	                        bool bNeedFree = true) const;

	MonoObject* GetObject(const void* InStruct) const;

	void* GetStruct(const MonoObject* InMonoObject) const;

	bool RemoveStructReference(const void* InStruct) const;

	bool RemoveStructReference(const MonoObject* InMonoObject) const;

public:
	template <typename T>
	auto GetContainer(const MonoObject* InMonoObject) const;

	template <typename T>
	auto GetContainer(const void* InAddress) const;

	MonoObject* GetContainerObject(const void* InContainer) const;

	bool AddContainerReference(void* InContainer, MonoObject* InMonoObject) const;

	bool AddContainerReference(void* InAddress, void* InContainer, MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveContainerReference(const MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveContainerReference(const void* InContainer) const;

public:
	template <typename T>
	auto GetDelegate(const void* InAddress) const;

	MonoObject* GetDelegateObject(const void* InDelegate) const;

	bool AddDelegateReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveDelegateReference(const MonoObject* InMonoObject) const;

	template <typename T>
	auto RemoveDelegateReference(const void* InDelegate) const;

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
	
private:
	static FCSharpEnvironment* Environment;

	FMonoDomain* Domain;

private:
	FDelegateHandle OnUnrealCSharpModuleInActiveDelegateHandle;

private:
	FClassRegistry* ClassRegistry;

	FObjectRegistry* ObjectRegistry;

	FStructRegistry* StructRegistry;

	FContainerRegistry* ContainerRegistry;

	FDelegateRegistry* DelegateRegistry;
};

#include "FCSharpEnvironment.inl"
