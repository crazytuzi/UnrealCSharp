#pragma once

#include "FFunctionInfo.h"
#include "FBindingFunction.h"

struct FBindingFunctionRegister
{
	FBindingFunctionRegister() = default;

	FBindingFunctionRegister(const FString& InName,
	                         const FString& InImplementationName,
	                         const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction):
		Name(InName),
		ImplementationName(InImplementationName),
		FunctionInfoFunction(InFunctionInfoFunction)
	{
	}

	explicit operator FBindingFunction() const
	{
		return FBindingFunction(Name,
		                        ImplementationName,
		                        FunctionInfoFunction.IsSet() ? FunctionInfoFunction.GetValue()() : nullptr);
	}

private:
	FString Name;

	FString ImplementationName;

	TOptional<TFunction<FFunctionInfo*()>> FunctionInfoFunction;
};
