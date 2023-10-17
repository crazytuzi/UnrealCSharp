#pragma once

#include "Reflection/Function/FFunctionDescriptor.h"
#include "mono/metadata/object-forward.h"

class FClassDescriptor
{
public:
	FClassDescriptor(UStruct* InStruct, MonoClass* InBindMonoClass);

	~FClassDescriptor();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoClass* GetMonoClass() const;

public:
	FFunctionDescriptor* GetFunctionDescriptor(const FName& InFunctionName);

	bool HasFunctionDescriptor(uint32 InFunctionHash) const;

	bool HasPropertyDescriptor(const FName& InPropertyName);

private:
	friend class FCSharpBind;

	TWeakObjectPtr<UStruct> Struct;

	MonoClass* BindMonoClass;

	TSet<uint32> PropertyHashSet;

	TSet<uint32> FunctionHashSet;
};
