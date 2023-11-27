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

	FClassDescriptor* AddClassDescriptor(const class FDomain* InDomain, UStruct* InStruct);

	void RemoveClassDescriptor(const UStruct* InStruct);

	FFunctionDescriptor* GetFunctionDescriptor(uint32 InFunctionHash);

	FFunctionDescriptor* GetOrAddFunctionDescriptor(uint32 InFunctionHash);

	FPropertyDescriptor* GetOrAddPropertyDescriptor(uint32 InPropertyHash);

	void AddFunctionDescriptor(uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor);

	void AddFunctionHash(uint32 InFunctionHash, FClassDescriptor* InClassDescriptor, const FName& InFunctionName);

	void RemoveFunctionDescriptor(uint32 InFunctionHash);

	void AddPropertyDescriptor(uint32 InPropertyHash, FPropertyDescriptor* InPropertyDescriptor);

	void AddPropertyHash(uint32 InPropertyHash, FClassDescriptor* InClassDescriptor, const FName& InPropertyName);

	void RemovePropertyDescriptor(uint32 InPropertyHash);

private:
	TMap<TWeakObjectPtr<const UStruct>, FClassDescriptor*> ClassDescriptorMap;

	TMap<uint32, TPair<FClassDescriptor*, FName>> PropertyHashMap;

	TMap<uint32, FPropertyDescriptor*> PropertyDescriptorMap;

	TMap<uint32, TPair<FClassDescriptor*, FName>> FunctionHashMap;

	TMap<uint32, FFunctionDescriptor*> FunctionDescriptorMap;
};
