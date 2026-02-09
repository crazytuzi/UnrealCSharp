#pragma once

#include "FReflection.h"

class UNREALCSHARPCORE_API FMethodReflection : FReflection
{
public:
	FMethodReflection(const FString& InName, bool InIsOverride, int32 InParamCount, MonoReflectionMethod* InReflectionMethod);

public:
	bool IsOverride() const;
	
	int32 GetParamCount() const;
	
	MonoMethod* GetMethod() const;
public:
	bool bIsOverride{};
	
	int32 ParamCount{};
	
	MonoReflectionMethod* ReflectionMethod{};
	
	MonoMethod* Method{};
};
