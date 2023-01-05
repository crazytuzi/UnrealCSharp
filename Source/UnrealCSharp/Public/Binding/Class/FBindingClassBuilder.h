#pragma once

#include "Macro/NamespaceMacro.h"

class FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InNameSpace = NAMESPACE_BINDING);

	virtual ~FBindingClassBuilder() = default;

	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod);

	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	FString Class;

	FString NameSpace;

	TMap<FString, const void*> Functions;
};
