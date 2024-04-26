#pragma once

#include "FBindingFunctionRegister.h"
#include "FBindingSubscript.h"

struct FBindingSubscriptRegister : FBindingFunctionRegister
{
	FBindingSubscriptRegister() = default;

	FBindingSubscriptRegister(const FString& InName,
	                          const FString& InImplementationName,
	                          const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction,
	                          const FString& InGetImplementationName,
	                          const FString& InSetImplementationName):
		FBindingFunctionRegister(InName, InImplementationName, InFunctionInfoFunction),
		GetImplementationName(InGetImplementationName),
		SetImplementationName(InSetImplementationName)
	{
	}

	explicit operator FBindingSubscript() const
	{
		return FBindingSubscript(operator FBindingFunction(), GetImplementationName, SetImplementationName);
	}

private:
	FString GetImplementationName;

	FString SetImplementationName;
};
