#pragma once

class UNREALCSHARP_API FBindingClassBuilder
{
public:
	explicit FBindingClassBuilder(const FString& InClass, const FString& InNameSpace);

	virtual ~FBindingClassBuilder() = default;

	FBindingClassBuilder& Property(const FString& InName, const void* InGetMethod, const void* InSetMethod);

	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	FString Class;

	FString NameSpace;

	TMap<FString, const void*> Functions;
};
