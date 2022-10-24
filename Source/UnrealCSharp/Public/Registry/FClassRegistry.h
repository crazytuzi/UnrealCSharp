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
	FClassDescriptor* GetClassDescriptor(const UClass* InClass);

	FClassDescriptor* NewClassDescriptor(const class FMonoDomain* InMonoDomain, UClass* InClass);

	void DeleteClassDescriptor(const UClass* InClass);

private:
	TMap<UClass*, FClassDescriptor*> ClassDescriptorMap;
};
