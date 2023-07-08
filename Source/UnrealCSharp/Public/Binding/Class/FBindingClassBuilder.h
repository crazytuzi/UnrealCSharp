#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "Macro/BindingMacro.h"

class UNREALCSHARP_API FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

#if WITH_PROPERTY_INFO
	explicit FBindingClassBuilder(const FString& InClass, FTypeInfo* InTypeInfo,
	                              const FString& InImplementationNameSpace);
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

private:
	FString Class;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FString, const void*> Functions;
};
