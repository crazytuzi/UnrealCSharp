#pragma once

#include "Binding/TypeInfo/FTypeInfo.h"

struct FFunctionInfo
{
	FFunctionInfo() = default;

	virtual ~FFunctionInfo() = default;

	virtual bool IsConstructor() const = 0;

	virtual bool IsDestructor() const = 0;

	virtual bool IsStatic() const = 0;

	virtual FTypeInfo* GetReturn() const = 0;

	virtual const TArray<FTypeInfo*>& GetParams() const = 0;
};
