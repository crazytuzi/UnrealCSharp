#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FNamePropertyDescriptor final : public FPropertyDescriptor
{
public:
	using FPropertyDescriptor::FPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;
};
