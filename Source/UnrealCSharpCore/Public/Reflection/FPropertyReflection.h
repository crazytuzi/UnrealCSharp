#pragma once

#include "FReflection.h"
#include "Domain/Script/IManagedHandle.h"

class FClassReflection;

class UNREALCSHARPCORE_API FPropertyReflection : public FReflection
{
public:
	FPropertyReflection(const FString& InName, const IManagedHandle InManagedProperty,
	                    FClassReflection* InReflectionType,
	                    const TSet<FClassReflection*>& InAttributes,
	                    const TMap<FClassReflection*, TArray<FString>>& InAttributeValues);

	~FPropertyReflection();

public:
	FClassReflection* GetReflectionType() const;

	bool IsUProperty() const;

public:
	void SetValue(const IManagedHandle InManagedHandle, void** InParams) const;

private:
	IManagedHandle ManagedProperty{InvalidManagedHandle};

	FClassReflection* ReflectionType{};

	bool bIsUProperty{};
};
