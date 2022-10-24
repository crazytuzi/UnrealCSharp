#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "Reflection/Function/FFunctionDescriptor.h"
#include "mono/metadata/object-forward.h"

class FClassDescriptor
{
public:
	FClassDescriptor(UClass* InClass, MonoClass* InBindMonoClass);

	~FClassDescriptor();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoClass* GetMonoClass() const;

public:
	FFunctionDescriptor* GetFunctionDescriptor(const FName& InFunctionName) const;

	FPropertyDescriptor* GetPropertyDescriptor(const FName& InPropertyName) const;

private:
	friend class FCSharpBind;

	UClass* Class;

	MonoClass* BindMonoClass;

	TMap<FName, FFunctionDescriptor*> FunctionDescriptorMap;

	TMap<FName, FPropertyDescriptor*> PropertyDescriptorMap;
};
