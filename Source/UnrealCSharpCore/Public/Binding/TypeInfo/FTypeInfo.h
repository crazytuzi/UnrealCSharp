#pragma once

#include "Binding/TypeInfo/FNameSpace.h"

struct FTypeInfo
{
	virtual ~FTypeInfo() = default;

	virtual FString GetClass() const = 0;

	virtual FNameSpace* GetNameSpace() const = 0;
};

struct FPrimitiveTypeInfo : FTypeInfo
{
	virtual FNameSpace* GetNameSpace() const override
	{
		return &FPrimitiveNameSpace::Instance;
	}
};

struct FCommonTypeInfo : FTypeInfo
{
	virtual FNameSpace* GetNameSpace() const override
	{
		return &FCommonNameSpace::Instance;
	}
};
