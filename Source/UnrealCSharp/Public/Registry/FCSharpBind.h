#pragma once

#include "Domain/FMonoDomain.h"
#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Function/FFunctionDescriptor.h"

class FCSharpBind
{
public:
	static bool Bind(FMonoDomain* InMonoDomain, UObject* InObject);

private:
	static bool Bind(FMonoDomain* InMonoDomain, UClass* InClass, bool bNeedMonoClass = true);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

private:
	static bool BindImplementation(FMonoDomain* InMonoDomain, UObject* InObject);

	static bool BindImplementation(FMonoDomain* InMonoDomain, UClass* InClass);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

private:
	static bool CanBind(const FMonoDomain* InMonoDomain, const UClass* InClass);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, const UClass* InClass,
	                                      UFunction* InFunction);

	static bool IsCallCSharpFunction(UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

	static void UpdateCallCSharpFunction(UFunction* InFunction);

	static void UpdateCallCSharpFunctionFlags(UFunction* InFunctionCallLua);
};
