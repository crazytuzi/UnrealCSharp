#pragma once

#include "Binding/Property/FBindingProperty.h"
#include "Binding/Function/EFunctionInteract.h"
#include "Binding/Function/FBindingFunction.h"
#include "Binding/Function/FBindingSubscript.h"

class UNREALCSHARPCORE_API FBindingClass
{
public:
	FBindingClass(const bool InIsReflection, const FString& InClass,
	              const FString& InBindingNameSpace, FTypeInfo* InTypeInfo):
		bIsReflection(InIsReflection),
		ImplementationNameSpace(InBindingNameSpace),
		Class(InClass),
		TypeInfo{InTypeInfo},
		Subscript(nullptr)
	{
	}

	~FBindingClass();

	static FBindingClass* GetClass(bool InIsReflection, const FString& InClass,
	                               const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo);

	static const TMap<FString, FBindingClass>& GetClasses();

public:
	bool IsReflection() const;

	const FString& GetImplementationNameSpace() const;

	const FString& GetBase() const;

	const FString& GetClass() const;

	const FBindingTypeInfo& GetTypeInfo() const;

	const FBindingSubscript* GetSubscript() const;

	const TArray<FBindingProperty>& GetProperties() const;

	const TArray<FBindingFunction>& GetFunctions() const;

public:
	void BindingSubscript(const FString& InName, const FString& InGetImplementationName,
	                      const FString& InSetImplementationName, FFunctionInfo* InTypeInfo,
	                      const TArray<FString>& InParamNames);

	void BindingProperty(const FString& InName, FTypeInfo* InTypeInfo, const void* InGetMethod,
	                     const void* InSetMethod);

	void BindingFunction(const FString& InName, const FString& InImplementationName,
	                     FFunctionInfo* InTypeInfo, const TArray<FString>& InParamNames,
	                     const EFunctionInteract InFunctionInteract);

	void Inheritance(const FString& InClass, const FString& InImplementationNameSpace, FTypeInfo* InTypeInfo);

private:
	static TMap<FString, FBindingClass> Classes;

	bool bIsReflection;

	FString ImplementationNameSpace;

	FString Base;

	FString Class;

	FBindingTypeInfo TypeInfo;

	FBindingSubscript* Subscript;

	TArray<FBindingProperty> Properties;

	TArray<FBindingFunction> Functions;
};
