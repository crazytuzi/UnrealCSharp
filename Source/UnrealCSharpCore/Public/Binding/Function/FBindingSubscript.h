#pragma once

#include "FBindingFunction.h"

struct FBindingSubscript : FBindingFunction
{
	FBindingSubscript(FFunctionInfo* InInfo, const FString& InName,
	                  const FString& InImplementationName, const TArray<FString>& InParamNames,
	                  const FString& InGetImplementationName, const FString& InSetImplementationName):
		FBindingFunction(InInfo, InName, InImplementationName, InParamNames),
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
