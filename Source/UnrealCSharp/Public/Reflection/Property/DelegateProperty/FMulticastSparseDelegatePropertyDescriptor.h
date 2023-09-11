#pragma once

#include "FMulticastDelegatePropertyDescriptor.h"

class FMulticastSparseDelegatePropertyDescriptor final : public FMulticastDelegatePropertyDescriptor
{
public:
	using FMulticastDelegatePropertyDescriptor::FMulticastDelegatePropertyDescriptor;

protected:
	virtual const FMulticastScriptDelegate* GetMulticastDelegate(void* InAddress) const override;
};
