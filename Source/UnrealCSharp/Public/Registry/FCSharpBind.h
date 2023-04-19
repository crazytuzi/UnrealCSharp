#pragma once

#include "Domain/FMonoDomain.h"
#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Container/FContainerHelper.h"
#include "Reflection/Function/FFunctionDescriptor.h"

class FCSharpBind
{
public:
	static MonoObject* Bind(FMonoDomain* InMonoDomain, UObject* InObject);

	static bool Bind(FMonoDomain* InMonoDomain, UObject* InObject, bool bNeedMonoClass);

	static bool Bind(FMonoDomain* InMonoDomain, UStruct* InStruct, bool bNeedMonoClass);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                 MonoReflectionType* InValueReflectionType);

	static bool Bind(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto Bind(MonoObject* InMonoObject);

private:
	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

private:
	static bool BindImplementation(FMonoDomain* InMonoDomain, UObject* InObject, bool bNeedMonoClass);

	static bool BindImplementation(FMonoDomain* InMonoDomain, UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType);

	static bool BindImplementation(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
	                               MonoReflectionType* InValueReflectionType);

	static bool BindImplementation(FMonoDomain* InMonoDomain, MonoObject* InMonoObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(MonoObject* InMonoObject);

private:
	static bool CanBind(const FMonoDomain* InMonoDomain, UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

	static void UpdateCallCSharpFunction(UFunction* InFunction);

	static void UpdateCallCSharpFunctionFlags(UFunction* InFunctionCallLua);

private:
	static bool IsOverrideType(const FMonoDomain* InMonoDomain, MonoReflectionType* InMonoReflectionType);

	static bool IsOverrideMethod(const FMonoDomain* InMonoDomain, MonoReflectionMethod* InMonoReflectionMethod);

#if !WITH_EDITOR
private:
	static TSet<TWeakObjectPtr<UStruct>> NotOverrideTypes;
#endif
};

#include "FCSharpBind.inl"
