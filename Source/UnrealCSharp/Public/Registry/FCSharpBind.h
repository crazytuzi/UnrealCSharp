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
	template <auto IsNeedMonoClass>
	static auto Bind(FDomain* InDomain, UStruct* InStruct);

	static MonoObject* Bind(FDomain* InDomain, UObject* InObject);

	static MonoObject* Bind(FDomain* InDomain, UClass* InClass);

	template <auto IsNeedMonoClass>
	static auto Bind(FDomain* InDomain, UObject* InObject);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                 MonoReflectionType* InValueReflectionType);

	static bool Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject);

	static bool Bind(FDomain* InDomain, FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	static bool BindClassDefaultObject(FDomain* InDomain, UObject* InObject);

private:
	template <auto IsNeedMonoClass>
	static auto BindImplementation(FDomain* InDomain, UObject* InObject) -> MonoObject*;

	static bool BindImplementation(FDomain* InDomain, UStruct* InStruct);

	static bool BindImplementation(FDomain* InDomain, FClassDescriptor* InClassDescriptor,
	                               UClass* InClass, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                               MonoReflectionType* InValueReflectionType);

	static bool BindImplementation(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject);

private:
	static bool CanBind(const FDomain* InDomain, UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(const UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

private:
	static bool IsOverrideType(const FDomain* InDomain, MonoReflectionType* InMonoReflectionType);

	static bool IsOverrideMethod(const FDomain* InDomain, MonoReflectionMethod* InMonoReflectionMethod);

private:
	void OnCSharpEnvironmentInitialize();

#if !WITH_EDITOR
private:
	static TSet<TWeakObjectPtr<UStruct>> NotOverrideTypes;
#endif

private:
	FDelegateHandle OnCSharpEnvironmentInitializeDelegateHandle;
};

#include "FCSharpBind.inl"
