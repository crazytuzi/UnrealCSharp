#pragma once

#include "Reflection/Class/FClassDescriptor.h"

class FClassRegistry
{
public:
	FClassRegistry();

	~FClassRegistry();

public:
	void Initialize();

	void Deinitialize();

public:
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct) const;

	FClassDescriptor* GetClassDescriptor(const FName& InClassName) const;

	FClassDescriptor* NewClassDescriptor(const class FDomain* InDomain, UStruct* InStruct);

	void DeleteClassDescriptor(const UStruct* InStruct);

	FPropertyDescriptor* GetPropertyDescriptor(const FDomain* InDomain, const UStruct* InStruct,
	                                           MonoString* InPropertyName);

	FFunctionDescriptor* GetFunctionDescriptor(const FDomain* InDomain, const UStruct* InStruct,
	                                           MonoString* InFunctionName);

private:
	TMap<TWeakObjectPtr<const UStruct>, FClassDescriptor*> ClassDescriptorMap;

	TMap<MonoString*, FPropertyDescriptor*> PropertyDescriptorMap;

	TMap<MonoString*, FFunctionDescriptor*> FunctionDescriptorMap;
};
