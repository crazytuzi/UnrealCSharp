#pragma once

#include "Reflection//FClassReflection.h"
#include "Reflection/Function/FFunctionDescriptor.h"
#include "mono/metadata/object-forward.h"

class UNREALCSHARP_API FClassDescriptor
{
public:
	FClassDescriptor(UStruct* InStruct);

	~FClassDescriptor();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoClass* GetMonoClass() const;
	
	MonoVTable* GetVTable() const;
	
	const TMap<FString, FPropertyReflection*>& GetProperties() const;
	
	const TMap<FString, FFieldReflection*>& GetField() const;
	
	const TMap<TPair<FString,int32>, FMethodReflection*>& GetMethods() const;
	
public:
	FFunctionDescriptor* GetFunctionDescriptor(const FString& InFunctionName);

	template <typename T, typename... Args>
	auto AddFunctionDescriptor(UFunction* InFunction, Args&&... InArgs) -> T*;

	FPropertyDescriptor* AddPropertyDescriptor(FProperty* InProperty);

	bool HasFunctionDescriptor(uint32 InFunctionHash) const;

private:
	TWeakObjectPtr<UStruct> Struct;

	MonoClass* BindMonoClass;
	
	FClassReflection* ClassReflection;

	TSet<uint32> PropertyHashSet;

	TSet<uint32> FunctionHashSet;
};

#include "FClassDescriptor.inl"
