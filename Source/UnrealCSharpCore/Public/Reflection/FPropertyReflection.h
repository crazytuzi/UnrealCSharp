#pragma once

#include "FReflection.h"
#include "Domain/FMonoDomain.h"

class FClassReflection;

class UNREALCSHARPCORE_API FPropertyReflection : public FReflection
{
public:
	FPropertyReflection(const FString& InName, MonoReflectionProperty* InReflectionProperty,
	                    MonoReflectionType* InReflectionType,
	                    const TSet<FClassReflection*>& InAttributes,
	                    const TMap<FClassReflection*, TArray<FString>>& InAttributeValues);

public:
	MonoReflectionProperty* GetReflectionProperty() const;

	MonoProperty* GetProperty() const;

	FClassReflection* GetReflectionType() const;

	bool IsUProperty() const;

public:
	void SetValue(void* InMonoObject, void** InParams, MonoObject** InExc) const;

	MonoObject* GetValue(void* InMonoObject, void** InParams, MonoObject** InExc) const;

private:
	MonoReflectionProperty* ReflectionProperty{};

	MonoProperty* Property{};

	MonoReflectionType* ReflectionType{};

	bool bIsUProperty{};
};
