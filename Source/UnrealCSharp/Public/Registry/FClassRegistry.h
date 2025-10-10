#pragma once

#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Function/FCSharpFunctionRegister.h"

class UNREALCSHARP_API FClassRegistry
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

	FClassDescriptor* AddClassDescriptor(UStruct* InStruct);

	static void AddClassConstructor(UClass* InClass);

	void RemoveClassDescriptor(const UStruct* InStruct);

	template <typename T>
	auto GetFunctionDescriptor(uint32 InFunctionHash) -> T*;

	template <typename T>
	auto GetOrAddFunctionDescriptor(const uint32 InFunctionHash) -> T*;

	FPropertyDescriptor* GetOrAddPropertyDescriptor(uint32 InPropertyHash);

	void AddFunctionDescriptor(uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor);

	template <typename T, typename... Args>
	auto AddFunctionHash(uint32 InFunctionHash, Args&&... InArgs) -> void;

	void RemoveFunctionDescriptor(uint32 InFunctionHash);

	void AddPropertyHash(uint32 InPropertyHash, FClassDescriptor* InClassDescriptor, FProperty* InProperty);

	void RemovePropertyDescriptor(uint32 InPropertyHash);

private:
	static void ClassConstructor(const FObjectInitializer& InObjectInitializer);

private:
	TMap<TWeakObjectPtr<const UStruct>, FClassDescriptor*> ClassDescriptorMap;

	TMap<uint32, std::tuple<FClassDescriptor*, FProperty*>> PropertyHashMap;

	TMap<uint32, FPropertyDescriptor*> PropertyDescriptorMap;

	TMap<uint32, std::tuple<FClassDescriptor*, UFunction*, FCSharpFunctionRegister>> CSharpFunctionHashMap;

	TMap<uint32, std::tuple<FClassDescriptor*, UFunction*>> UnrealFunctionHashMap;

	TMap<uint32, FFunctionDescriptor*> FunctionDescriptorMap;

	static TMap<TWeakObjectPtr<UClass>, UClass::ClassConstructorType> ClassConstructorMap;
};

#include "FClassRegistry.inl"
