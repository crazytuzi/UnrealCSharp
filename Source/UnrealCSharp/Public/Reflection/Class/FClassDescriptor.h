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
	UNREALCSHARP_API MonoClass* GetMonoClass() const;

public:
	FFunctionDescriptor* AddFunctionDescriptor(const FString& InFunctionName);

	FFunctionDescriptor* GetOrAddFunctionDescriptor(const FString& InFunctionName);

	FPropertyDescriptor* AddPropertyDescriptor(const FString& InPropertyName);

	bool HasFunctionDescriptor(uint32 InFunctionHash) const;

	bool HasPropertyDescriptor(const FString& InPropertyName);

private:
	friend class FCSharpBind;

	TWeakObjectPtr<UStruct> Struct;

	MonoClass* BindMonoClass;

	TSet<uint32> PropertyHashSet;

	TSet<uint32> FunctionHashSet;
};
