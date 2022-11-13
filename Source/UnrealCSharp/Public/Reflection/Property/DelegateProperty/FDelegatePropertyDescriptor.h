#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FDelegatePropertyDescriptor final : public FPropertyDescriptor
{
public:
	using FPropertyDescriptor::FPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;
};
