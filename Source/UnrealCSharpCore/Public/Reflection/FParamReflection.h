#pragma once

#include "FReflection.h"

class FClassReflection;

class FParamReflection : public FReflection
{
public:
	FParamReflection(const FString& InName, bool InIsRef, FClassReflection* InReflectionType);

public:
	bool IsRef() const;

	FClassReflection* GetReflectionType() const;

private:
	bool bIsRef{};

	FClassReflection* ReflectionType{};
};
