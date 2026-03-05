#pragma once

#include "Domain/FDomain.h"
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

	static MonoObject* Bind(UObject* InObject);

	static MonoObject* Bind(UClass* InClass);

	template <auto IsNeedOverride>
	static auto Bind(UObject* InObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                 MonoObject* InMonoObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                 FClassReflection* InValueClassReflection, MonoObject* InMonoObject);

	static bool Bind(MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, MonoObject* InMonoObject);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	static bool Bind(FClassDescriptor* InClassDescriptor,
	                 UClass* InClass, const FString& InMethodName, UFunction* InFunction);

	static bool BindClassDefaultObject(UObject* InObject);

private:
	template <auto IsNeedOverride>
	static auto BindImplementation(UObject* InObject) -> MonoObject*;

	static bool BindImplementation(UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass,
	                               const FString& InMethodName, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                               MonoObject* InMonoObject);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                               FClassReflection* InValueClassReflection, MonoObject* InMonoObject);

	static bool BindImplementation(MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, MonoObject* InMonoObject);

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
