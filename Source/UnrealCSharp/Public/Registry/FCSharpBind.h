#pragma once

#include "Reflection/Class/FClassDescriptor.h"

class UNREALCSHARP_API FCSharpBind
{
public:
	FCSharpBind();

	~FCSharpBind();

public:
	void Initialize();

	void Deinitialize();

public:
	template <auto IsNeedOverride>
	static auto Bind(UStruct* InStruct);

	static IManagedHandle Bind(UObject* InObject);

	static IManagedHandle Bind(UClass* InClass);

	template <auto IsNeedOverride>
	static auto Bind(UObject* InObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                 const IManagedHandle InManagedObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                 FClassReflection* InValueClassReflection, const IManagedHandle InManagedObject);

	static bool Bind(const IManagedHandle InManagedObject, const FName& InStructName);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, const IManagedHandle InManagedObject);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	static bool Bind(FClassDescriptor* InClassDescriptor,
	                 UClass* InClass, const FString& InMethodName, UFunction* InFunction);

	static bool BindClassDefaultObject(UObject* InObject);

private:
	template <auto IsNeedOverride>
	static auto BindImplementation(UObject* InObject) -> IManagedHandle;

	static bool BindImplementation(UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass,
	                               const FString& InMethodName, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                               const IManagedHandle InManagedObject);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                               FClassReflection* InValueClassReflection, const IManagedHandle InManagedObject);

	static bool BindImplementation(const IManagedHandle InManagedObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, const IManagedHandle InManagedObject);

private:
	static bool CanBind(UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(const UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

private:
	void OnCSharpEnvironmentInitialize();

private:
	static TSet<TWeakObjectPtr<UStruct>> NotOverrideTypes;

	FDelegateHandle OnCSharpEnvironmentInitializeDelegateHandle;
};

#include "FCSharpBind.inl"
