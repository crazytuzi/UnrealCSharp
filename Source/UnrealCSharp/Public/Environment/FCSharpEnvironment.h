#pragma once

#include "Domain/FMonoDomain.h"
#include "Registry/FClassRegistry.h"
#include "Registry/FObjectRegistry.h"

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

public:
	FClassDescriptor* GetClassDescriptor(const UClass* InClass) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* NewClassDescriptor(const FMonoDomain* InMonoDomain, UClass* InClass) const;

	void DeleteClassDescriptor(const UClass* InClass) const;

	FFunctionDescriptor* GetFunctionDescriptor(const UClass* InClass, const FName& InFunctionName) const;

	FFunctionDescriptor* GetFunctionDescriptor(const FName& InClassName, const FName& InFunctionName) const;

	FPropertyDescriptor* GetPropertyDescriptor(const UClass* InClass, const FName& InPropertyName) const;

public:
	bool AddReference(UObject* InObject, MonoObject* InMonoObject) const;

	MonoObject* GetObject(const UObject* InObject) const;

	UObject* GetObject(const MonoObject* InMonoObject) const;

	bool RemoveReference(const UObject* InObject) const;

	bool RemoveReference(const MonoObject* InMonoObject) const;

private:
	static FCSharpEnvironment* Environment;

	static FMonoDomain* Domain;

private:
	FDelegateHandle OnUnrealCSharpModuleInActiveDelegateHandle;

private:
	FClassRegistry* ClassRegistry;

	FObjectRegistry* ObjectRegistry;
};
