#pragma once

#include "FReflection.h"
class UNREALCSHARPCORE_API FFieldReflection : FReflection
{
public:
	FFieldReflection(const FString& InName, MonoReflectionField* InReflectionField);

public:
	MonoClassField* GetField() const;
	
private:
	MonoReflectionField* ReflectionField{};
	
	MonoClassField* Field{};
};
