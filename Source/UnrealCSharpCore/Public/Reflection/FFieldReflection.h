#pragma once

#include "FReflection.h"
#include "Domain/FMonoDomain.h"

class FClassReflection;

class UNREALCSHARPCORE_API FFieldReflection : public FReflection
{
public:
	FFieldReflection(const FString& InName, MonoReflectionField* InReflectionField);

public:
	MonoClassField* GetField() const;

public:
	void SetValue(const FClassReflection* InClass, void* InValue) const;

	MonoObject* GetValue(MonoObject* InMonoObject) const;

private:
	MonoReflectionField* ReflectionField{};

	MonoClassField* Field{};
};
