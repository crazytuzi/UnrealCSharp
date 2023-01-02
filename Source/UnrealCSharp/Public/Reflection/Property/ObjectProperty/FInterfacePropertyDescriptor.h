#pragma once

#include "FObjectPropertyDescriptor.h"

class FInterfacePropertyDescriptor final : public FObjectPropertyDescriptor
{
public:
	using FObjectPropertyDescriptor::FObjectPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;
};
