#pragma once

#include "FBindingMethod.h"

struct FBindingMethodRegister
{
	FBindingMethodRegister(const TFunction<FString()>& InMethodFunction, const void* InFunction):
		MethodFunction(InMethodFunction),
		Function(InFunction)
	{
	}

	explicit operator FBindingMethod() const
	{
		return FBindingMethod(MethodFunction(), Function);
	}

private:
	TFunction<FString()> MethodFunction;

	const void* Function;
};
