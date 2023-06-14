#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "Macro/BindingMacro.h"

class UNREALCSHARP_API FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InImplementationNameSpace);

#if WITH_TYPE_INFO
	explicit FBindingClassBuilder(const FString& InClass, FTypeInfo* InTypeInfo,
	                              const FString& InImplementationNameSpace);
#endif

	virtual ~FBindingClassBuilder() = default;

#if WITH_TYPE_INFO
	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod,
	                               FTypeInfo* InTypeInfo = nullptr);
#else
	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod);
#endif

	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	FString Class;

	FTypeInfo* TypeInfo;

	FString ImplementationNameSpace;

	TMap<FString, const void*> Functions;
};
