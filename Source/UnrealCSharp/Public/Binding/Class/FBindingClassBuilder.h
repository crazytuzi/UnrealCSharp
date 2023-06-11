#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"

class UNREALCSHARP_API FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

	explicit FBindingClassBuilder(const FString& InClass, FTypeInfo* InTypeInfo,
	                              const FString& InImplementationNameSpace);

	virtual ~FBindingClassBuilder() = default;

	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod,
	                               FTypeInfo* InTypeInfo = nullptr);

	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	FString Class;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FString, const void*> Functions;
};
