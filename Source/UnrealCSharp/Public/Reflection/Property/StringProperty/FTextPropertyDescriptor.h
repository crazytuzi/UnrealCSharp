#pragma once

#include "Reflection/Property/FCompoundPropertyDescriptor.h"

class FTextPropertyDescriptor final : public FCompoundPropertyDescriptor
{
public:
	explicit FTextPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;

private:
	MonoObject* NewWeakRef(void* InAddress) const;
};
