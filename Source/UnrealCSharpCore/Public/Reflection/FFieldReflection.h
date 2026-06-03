#pragma once

#include "FReflection.h"
#include "Domain/Script/IManagedTypes.h"

class FClassReflection;

class UNREALCSHARPCORE_API FFieldReflection : public FReflection
{
public:
	FFieldReflection(const FString& InName, const IManagedReflectionField InManagedReflectionField);

	~FFieldReflection();

public:
	void SetValue(const FClassReflection* InClass, void* InValue) const;

private:
	IManagedReflectionField ManagedReflectionField{INVALID_MANAGED};
};
