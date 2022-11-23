#pragma once

class FBindingClassBuilder
{
public:
	FBindingClassBuilder();

public:
	FBindingClassBuilder& Function(const FString& InName, const void* InMethod);

	void Register();

private:
	TMap<FString, const void*> Functions;
};
