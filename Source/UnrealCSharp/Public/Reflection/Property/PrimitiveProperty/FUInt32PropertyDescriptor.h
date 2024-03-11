#pragma once

#include "FPrimitivePropertyDescriptor.h"

class FUInt32PropertyDescriptor final : public FPrimitivePropertyDescriptor
{
public:
	using FPrimitivePropertyDescriptor::FPrimitivePropertyDescriptor;

	void Set(void* Src, void* Dest) const override;
};
