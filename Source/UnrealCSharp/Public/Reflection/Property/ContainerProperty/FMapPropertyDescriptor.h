#pragma once

#include "FContainerPropertyDescriptor.h"

class FMapPropertyDescriptor final : public FContainerPropertyDescriptor
{
public:
	using FContainerPropertyDescriptor::FContainerPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;
};
