#pragma once

#include "Reflection/Class/FClassDescriptor.h"

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

	FFunctionDescriptor* GetFunctionDescriptor(uint32 InFunctionHash);

	FFunctionDescriptor* GetOrAddFunctionDescriptor(uint32 InFunctionHash);

	FPropertyDescriptor* GetOrAddPropertyDescriptor(uint32 InPropertyHash);

	void AddFunctionDescriptor(uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor);

	void AddFunctionHash(uint32 InFunctionHash, FClassDescriptor* InClassDescriptor, const FString& InFunctionName);

	void RemoveFunctionDescriptor(uint32 InFunctionHash);

	void AddPropertyDescriptor(uint32 InPropertyHash, FPropertyDescriptor* InPropertyDescriptor);

	void AddPropertyHash(uint32 InPropertyHash, FClassDescriptor* InClassDescriptor, const FString& InPropertyName);

	void RemovePropertyDescriptor(uint32 InPropertyHash);

private:
	static void ClassConstructor(const FObjectInitializer& InObjectInitializer);

private:
	TMap<TWeakObjectPtr<const UStruct>, FClassDescriptor*> ClassDescriptorMap;

	TMap<uint32, TPair<FClassDescriptor*, FString>> PropertyHashMap;

	TMap<uint32, FPropertyDescriptor*> PropertyDescriptorMap;

	TMap<uint32, TPair<FClassDescriptor*, FString>> FunctionHashMap;

	TMap<uint32, FFunctionDescriptor*> FunctionDescriptorMap;

	static TMap<TWeakObjectPtr<UClass>, UClass::ClassConstructorType> ClassConstructorMap;
};
