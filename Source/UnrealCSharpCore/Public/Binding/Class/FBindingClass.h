#pragma once

#include "Binding/Property/FBindingProperty.h"
#include "Binding/Function/FBindingFunction.h"

class UNREALCSHARPCORE_API FBindingClass
{
public:
	FBindingClass(const bool InIsReflection, const FString& InClass, const FString& InFullClass,
	              const FString& InBindingNameSpace, FTypeInfo* InTypeInfo):
		bIsReflection(InIsReflection),
		ImplementationNameSpace(InBindingNameSpace),
		Class(InClass),
		FullClass(InFullClass),
		TypeInfo{InTypeInfo}
	{
	}

	static FBindingClass* GetClass(bool InIsReflection, const FString& InClass, const FString& InFullClass,
	                               const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo);

	static const TMap<FString, FBindingClass>& GetClasses();

public:
	bool IsReflection() const;

	const FString& GetImplementationNameSpace() const;

	const FString& GetBase() const;

	const FString& GetClass() const;

	const FString& GetFullClass() const;

	const FBindingTypeInfo& GetTypeInfo() const;

	const TArray<FBindingProperty>& GetProperties() const;

	const TArray<FBindingFunction>& GetFunctions() const;

public:
	void BindingProperty(const FString& InName, FTypeInfo* InTypeInfo, const void* InGetMethod,
	                     const void* InSetMethod);

	void BindingFunction(const FString& InName, const FString& InImplementationName, FFunctionInfo* InTypeInfo);

	void Inheritance(const FString& InClass, const FString& InFullClass,
	                 const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo);

private:
	static TMap<FString, FBindingClass> Classes;

	bool bIsReflection;

	FString ImplementationNameSpace;

	FString Base;

	FString Class;

	FString FullClass;

	FBindingTypeInfo TypeInfo;

	TArray<FBindingProperty> Properties;

	TArray<FBindingFunction> Functions;
};
