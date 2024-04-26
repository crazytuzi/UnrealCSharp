#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"
#include "FBindingTypeInfo.h"

struct FBindingTypeInfoRegister
{
	explicit FBindingTypeInfoRegister(const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
		TypeInfoFunction(InTypeInfoFunction)
	{
	}

	explicit operator FBindingTypeInfo() const
	{
		return FBindingTypeInfo(TypeInfoFunction.IsSet() ? TypeInfoFunction.GetValue()() : nullptr);
	}

private:
	TOptional<TFunction<FTypeInfo*()>> TypeInfoFunction;
};
