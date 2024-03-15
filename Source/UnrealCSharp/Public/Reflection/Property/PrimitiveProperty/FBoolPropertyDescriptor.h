#pragma once

#include "FPrimitivePropertyDescriptor.h"

class FBoolPropertyDescriptor final : public FPrimitivePropertyDescriptor
{
public:
	using FPrimitivePropertyDescriptor::FPrimitivePropertyDescriptor;

	virtual void Set(void* Src, void* Dest) const override;
};
