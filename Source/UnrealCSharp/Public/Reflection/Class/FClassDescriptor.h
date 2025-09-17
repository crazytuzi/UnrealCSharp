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
	FFunctionDescriptor* GetFunctionDescriptor(const FString& InFunctionName);

	template <typename T, typename... Args>
	auto AddFunctionDescriptor(UFunction* InFunction, Args&&... InArgs) -> T*;

	FPropertyDescriptor* AddPropertyDescriptor(FProperty* InProperty);

	bool HasFunctionDescriptor(uint32 InFunctionHash) const;

private:
	TWeakObjectPtr<UStruct> Struct;

	MonoClass* BindMonoClass;

	TSet<uint32> PropertyHashSet;

	TSet<uint32> FunctionHashSet;
};

#include "FClassDescriptor.inl"
