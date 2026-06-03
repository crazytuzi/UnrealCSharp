#pragma once

#include "FReflection.h"
#include "Domain/Script/IManagedTypes.h"

class FClassReflection;

class UNREALCSHARPCORE_API FPropertyReflection : public FReflection
{
public:
	FPropertyReflection(const FString& InName, const IManagedReflectionProperty InManagedReflectionProperty,
	                    FClassReflection* InReflectionType,
	                    const TSet<FClassReflection*>& InAttributes,
	                    const TMap<FClassReflection*, TArray<FString>>& InAttributeValues);

	~FPropertyReflection();

public:
	FClassReflection* GetReflectionType() const;

	bool IsUProperty() const;

public:
	void SetValue(const IManagedHandle InManagedHandle, void** InParams) const;

	void* GetValue(const IManagedHandle InManagedHandle, void** InParams) const;

private:
	IManagedReflectionProperty ManagedReflectionProperty{INVALID_MANAGED};

	FClassReflection* ReflectionType{};

	bool bIsUProperty{};
};
