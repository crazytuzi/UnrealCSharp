#pragma once

#include "FBindingFunction.h"

struct FBindingSubscript : FBindingFunction
{
	FBindingSubscript(FFunctionInfo* InInfo, const FString& InName, const FString& InImplementationName,
	                  const FString& InGetImplementationName, const FString& InSetImplementationName):
		FBindingFunction(InInfo, InName, InImplementationName),
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
