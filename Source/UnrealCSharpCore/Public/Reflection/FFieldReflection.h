#pragma once

#include "FReflection.h"
#include "Domain/Script/IManagedHandle.h"

class FClassReflection;

class UNREALCSHARPCORE_API FFieldReflection : public FReflection
{
public:
	FFieldReflection(const FString& InName, const IManagedHandle InManagedField);

	~FFieldReflection();

public:
	void SetValue(const FClassReflection* InClass, void* InValue) const;

private:
	IManagedHandle ManagedField{InvalidManagedHandle};
};
