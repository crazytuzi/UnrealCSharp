#pragma once

#include "FContainerPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FMapPropertyDescriptor final : public FContainerPropertyDescriptor
{
public:
	using FContainerPropertyDescriptor::FContainerPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* Object_New(void* InAddress) const;
};
