#pragma once

#include "Domain/FMonoDomain.h"

class UNREALCSHARPCORE_API FReflection
{
public:
	FReflection(const FString& InName);
	
public:
	const FString& GetName();
	
protected:
	FString Name;
};
