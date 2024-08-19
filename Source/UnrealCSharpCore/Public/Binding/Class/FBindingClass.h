#pragma once

#include "Binding/TypeInfo/FBindingTypeInfo.h"
#include "Binding/Function/FBindingSubscript.h"
#include "Binding/Property/FBindingProperty.h"
#include "Binding/Function/FBindingFunction.h"
#include "Binding/Function/FBindingMethod.h"

class UNREALCSHARPCORE_API FBindingClass
{
public:
	FBindingClass(const FString& InBaseClass,
	              const FString& InClass,
	              const FString& InImplementationNameSpace,
	              const bool InIsProjectClass,
	              const bool InIsReflectionClass,
	              const FBindingTypeInfo& InTypeInfo,
	              const FBindingSubscript& InSubscript,
	              const TArray<FBindingProperty>& InProperties,
	              const TArray<FBindingFunction>& InFunctions,
	              const TArray<FBindingMethod>& InMethods);

	static TSet<FString> GetPropertyNames(const FString& InClass);

	static TSet<FString> GetFunctionNames(const FString& InClass);

public:
	const FString& GetBaseClass() const;

	const FString& GetClass() const;

	const FString& GetImplementationNameSpace() const;

	bool IsProjectClass() const;

	bool IsReflectionClass() const;

	bool IsSet() const;

	const FBindingTypeInfo& GetTypeInfo() const;

	const FBindingSubscript& GetSubscript() const;

	const TArray<FBindingProperty>& GetProperties() const;

	const TArray<FBindingFunction>& GetFunctions() const;

	const TArray<FBindingMethod>& GetMethods() const;

private:
	FString BaseClass;

	FString Class;

	FString ImplementationNameSpace;

	bool bIsProjectClass;

	bool bIsReflectionClass;

	FBindingTypeInfo TypeInfo;

	FBindingSubscript Subscript;

	TArray<FBindingProperty> Properties;

	TArray<FBindingFunction> Functions;

	TArray<FBindingMethod> Methods;
};
