#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FDelegatePropertyDescriptor final : public FPropertyDescriptor
{
public:
	using FPropertyDescriptor::FPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* Object_New(void* InAddress) const;
};
