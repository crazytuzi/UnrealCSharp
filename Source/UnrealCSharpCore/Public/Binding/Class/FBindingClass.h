#pragma once

#include "Binding/Property/FBindingProperty.h"
#include "Binding/Function/FBindingFunction.h"

class UNREALCSHARPCORE_API FBindingClass
{
public:
	FBindingClass(const FString& InBindingNameSpace, FTypeInfo* InTypeInfo):
		ImplementationNameSpace(InBindingNameSpace),
		TypeInfo{InTypeInfo}
	{
	}

	static FBindingClass* GetClass(const FString& InClass, const FString& InImplementationNameSpace,
	                               FTypeInfo* InTypeInfo);

	static const TMap<FString, FBindingClass>& GetClasses();

public:
	const FString& GetImplementationNameSpace() const;

	const FBindingTypeInfo& GetTypeInfo() const;

	const TArray<FBindingProperty>& GetProperties() const;

	const TArray<FBindingFunction>& GetFunctions() const;

public:
	void BindingProperty(const FString& InName, FTypeInfo* InTypeInfo, const void* InGetMethod,
	                     const void* InSetMethod);

	void BindingFunction(const FString& InName, const FString& InImplementationName, FFunctionInfo* InTypeInfo);

private:
	static TMap<FString, FBindingClass> Classes;

	FString ImplementationNameSpace;

	FBindingTypeInfo TypeInfo;

	TArray<FBindingProperty> Properties;

	TArray<FBindingFunction> Functions;
};
