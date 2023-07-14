#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "Macro/BindingMacro.h"
#include "Binding/Function/FBindingFunctionBase.inl"

class UNREALCSHARP_API FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

#if WITH_PROPERTY_INFO
	explicit FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace,
	                              FTypeInfo* InTypeInfo);
#endif

	virtual ~FBindingClassBuilder() = default;

#if WITH_PROPERTY_INFO
	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod,
	                               FTypeInfo* InTypeInfo = nullptr);
#else
	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod);
#endif

#if WITH_FUNCTION_INFO
	FBindingClassBuilder& Function(const FString& InName, const void* InMethod,
	                               FFunctionInfo* InFunctionInfo = nullptr);
#else
	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);
#endif

	void Register();

protected:
#if WITH_FUNCTION_INFO
	FBindingClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                               const void* InMethod, FFunctionInfo* InFunctionInfo = nullptr);
#else
	FBindingClassBuilder& Function(const FString& InName, const FString& InImplementationName,
	                               const void* InMethod);
#endif

private:
	FString GetFunctionImplementationName(const FString& InName) const;

	int32 GetFunctionCount(const FString& InName) const;

private:
	FString Class;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FBindingFunctionBase, const void*> Functions;
};
