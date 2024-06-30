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
	static MonoObject* Bind(FDomain* InDomain, UObject* InObject);

	static MonoObject* Bind(FDomain* InDomain, UClass* InClass);

	static bool Bind(FDomain* InDomain, UObject* InObject, bool bNeedMonoClass);

	static bool Bind(FDomain* InDomain, UStruct* InStruct, bool bNeedMonoClass);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                 MonoReflectionType* InValueReflectionType);

	static bool Bind(FDomain* InDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, const FString& InName,
	                 UFunction* InFunction);

	static bool BindClassDefaultObject(FDomain* InDomain, UObject* InObject);

private:
	static bool BindImplementation(FDomain* InDomain, UObject* InObject, bool bNeedMonoClass);

	static bool BindImplementation(FDomain* InDomain, UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, const FString& InName,
	                               UFunction* InFunction);

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
