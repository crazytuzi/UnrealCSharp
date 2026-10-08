#pragma once

#include "FBindingMethod.h"

struct FBindingMethodRegister
{
	FBindingMethodRegister(const TFunction<FString()>& InMethodFunction, const void* InFunction,
	                       const int32 InParamCount = INDEX_NONE) :
		MethodFunction(InMethodFunction),
		Function(InFunction),
		ParamCount(InParamCount)
	{
	}

	explicit operator FBindingMethod() const
	{
		return FBindingMethod(MethodFunction(), Function, ParamCount);
	}

private:
	TFunction<FString()> MethodFunction;

	const void* Function;

	int32 ParamCount{INDEX_NONE};
};
