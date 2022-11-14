#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FMulticastDelegatePropertyDescriptor : public FPropertyDescriptor
{
public:
	using FPropertyDescriptor::FPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;
};
