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
	FClassDescriptor* GetClassDescriptor(const UStruct* InStruct);

	FClassDescriptor* GetClassDescriptor(const FName& InClassName);

	FClassDescriptor* NewClassDescriptor(const class FDomain* InDomain, UStruct* InStruct);

	void DeleteClassDescriptor(const UStruct* InStruct);

private:
	TMap<TWeakObjectPtr<const UStruct>, FClassDescriptor*> ClassDescriptorMap;
};
