#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FEnumPropertyDescriptor final : public FPropertyDescriptor
{
public:
	using FPropertyDescriptor::FPropertyDescriptor;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual void DestroyValue(void* Dest) const override;

	virtual bool IsPrimitiveProperty() const override;
};
