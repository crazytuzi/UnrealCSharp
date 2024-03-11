#pragma once

#include "FPrimitivePropertyDescriptor.h"

class FInt64PropertyDescriptor final : public FPrimitivePropertyDescriptor
{
public:
	using FPrimitivePropertyDescriptor::FPrimitivePropertyDescriptor;

	void Set(void* Src, void* Dest) const override;
};
