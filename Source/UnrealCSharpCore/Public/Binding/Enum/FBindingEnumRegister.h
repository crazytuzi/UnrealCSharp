#pragma once

#include "Binding/TypeInfo/FBindingTypeInfoRegister.h"
#include "FBindingEnum.h"

class UNREALCSHARPCORE_API FBindingEnumRegister
{
public:
	FBindingEnumRegister(const TFunction<FString()>& InEnumFunction,
	                     const FString& InUnderlyingType,
	                     bool InIsProjectEnum,
	                     const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction);

	explicit operator FBindingEnum*() const;

public:
	void BindingEnumerator(const FString& InKey, int64 InEnumerator);

private:
	TFunction<FString()> EnumFunction;

	FString UnderlyingType;

	bool bIsProjectEnum;

	FBindingTypeInfoRegister TypeInfoRegister;

	TMap<FString, int64> Enumerators;
};
