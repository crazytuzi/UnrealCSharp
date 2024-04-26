#pragma once

#include "FBindingFunction.h"

struct FBindingSubscript : FBindingFunction
{
	FBindingSubscript() = default;

	FBindingSubscript(const FBindingFunction& InFunction,
	                  const FString& InGetImplementationName,
	                  const FString& InSetImplementationName):
		FBindingFunction(InFunction),
		GetImplementationName(InGetImplementationName),
		SetImplementationName(InSetImplementationName)
	{
	}

	const FString& GetGetImplementationName() const
	{
		return GetImplementationName;
	}

	const FString& GetSetImplementationName() const
	{
		return SetImplementationName;
	}

private:
	FString GetImplementationName;

	FString SetImplementationName;
};
