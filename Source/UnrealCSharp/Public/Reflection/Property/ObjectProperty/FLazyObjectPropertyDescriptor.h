#pragma once

#include "FObjectPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FLazyObjectPropertyDescriptor final : public FObjectPropertyDescriptor
{
public:
	using FObjectPropertyDescriptor::FObjectPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* Object_New(void* InAddress) const;
};
