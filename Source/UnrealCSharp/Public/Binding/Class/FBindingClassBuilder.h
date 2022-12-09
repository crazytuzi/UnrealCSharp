#pragma once

class FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass);

	virtual ~FBindingClassBuilder() = default;

	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod);

	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	FString Class;

	TMap<FString, const void*> Functions;
};
