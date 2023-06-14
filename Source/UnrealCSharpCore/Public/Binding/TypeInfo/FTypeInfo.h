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
		static FPrimitiveNameSpace Instance;

		return &Instance;
	}
};
