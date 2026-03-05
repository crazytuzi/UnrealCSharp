#pragma once

#include "FReflection.h"
#include "Domain/FMonoDomain.h"

class FClassReflection;

class FParamReflection : public FReflection
{
public:
	FParamReflection(const FString& InName, bool InIsRef, MonoReflectionType* InReflectionType);

public:
	bool IsRef() const;

	FClassReflection* GetReflectionType() const;

private:
	bool bIsRef{};

	MonoReflectionType* ReflectionType{};
};
