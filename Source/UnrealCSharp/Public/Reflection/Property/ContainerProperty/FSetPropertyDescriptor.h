#pragma once

#include "FContainerPropertyDescriptor.h"

class FSetPropertyDescriptor final : public FContainerPropertyDescriptor
{
public:
	using FContainerPropertyDescriptor::FContainerPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* NewRef(void* InAddress) const;

	MonoObject* NewWeakRef(void* InAddress) const;
};
