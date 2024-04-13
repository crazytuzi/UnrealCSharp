#pragma once

#include "Reflection/Property/FPrimitivePropertyDescriptor.h"

class FEnumPropertyDescriptor final : public FPrimitivePropertyDescriptor
{
public:
	using FPrimitivePropertyDescriptor::FPrimitivePropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual void DestroyValue(void* Dest) const override;
};
