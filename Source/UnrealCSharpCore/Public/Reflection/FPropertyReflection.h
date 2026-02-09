#pragma once

#include "FReflection.h"

class UNREALCSHARPCORE_API FPropertyReflection : public FReflection
{
public:
	FPropertyReflection(const FString& InName, MonoReflectionProperty* InReflectionProperty);

public:
	MonoProperty* GetProperty() const;
	
private:
	MonoReflectionProperty* ReflectionProperty{};
	
	MonoProperty* Property{};
};
