#pragma once

#include "FBindingClass.h"
#include "Binding/Function/FBindingSubscriptRegister.h"
#include "Binding/Property/FBindingPropertyRegister.h"
#include "Binding/Function/FBindingFunctionRegister.h"
#include "Binding/Function/FBindingMethodRegister.h"

class UNREALCSHARPCORE_API FBindingClassRegister
{
public:
	FBindingClassRegister(const TFunction<FString()>& InClassFunction,
	                      const FString& InImplementationNameSpace,
	                      const TFunction<bool()>& InIsProjectClassFunction,
	                      bool InIsReflectionClass,
	                      const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

	explicit operator FBindingClass*() const;

public:
	FString GetClass() const;

	bool IsReflectionClass() const;

public:
	void BindingSubscript(const FString& InName,
	                      const FString& InGetImplementationName,
	                      const FString& InSetImplementationName,
	                      const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction);

	void BindingProperty(const FString& InName,
	                     const void* InGetMethod,
	                     const void* InSetMethod,
	                     const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction);

	void BindingFunction(const FString& InName,
	                     const FString& InImplementationName,
	                     const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction);

	void BindingMethod(const FString& InImplementationName, const void* InFunction);

	void Inheritance(const TFunction<FString()>& InBaseClassFunction,
	                 const FString& InImplementationNameSpace,
	                 const TFunction<bool()>& InIsProjectClassFunction,
	                 bool InIsReflectionClass,
	                 const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction = {});

private:
	TOptional<TFunction<FString()>> BaseClassFunction;

	TFunction<FString()> ClassFunction;

	FString ImplementationNameSpace;

	TFunction<bool()> IsProjectClassFunction;

	bool bIsReflectionClass;

	FBindingTypeInfoRegister TypeInfoRegister;

	FBindingSubscriptRegister SubscriptRegister;

	TArray<FBindingPropertyRegister> PropertyRegisters;

	TArray<FBindingFunctionRegister> FunctionRegisters;

	TArray<FBindingMethodRegister> MethodRegisters;
};
