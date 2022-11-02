#pragma once

#include "Domain/FMonoDomain.h"
#include "Registry/FClassRegistry.h"
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
	void* GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct) const;

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

private:
	static FCSharpEnvironment* Environment;

	static FMonoDomain* Domain;

private:
	FDelegateHandle OnUnrealCSharpModuleInActiveDelegateHandle;

private:
	FClassRegistry* ClassRegistry;

	FObjectRegistry* ObjectRegistry;

	FStructRegistry* StructRegistry;
};
