#pragma once

#include "Reflection/Property/FCompoundPropertyDescriptor.h"

class FDelegatePropertyDescriptor final : public FCompoundPropertyDescriptor
{
public:
	using FCompoundPropertyDescriptor::FCompoundPropertyDescriptor;

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* NewRef(void* InAddress) const;

	MonoObject* NewWeakRef(void* InAddress) const;
};
