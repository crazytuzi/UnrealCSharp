#pragma once

#include "FObjectPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"
#include "mono/metadata/details/class-types.h"

class FWeakObjectPropertyDescriptor final : public FObjectPropertyDescriptor
{
public:
	explicit FWeakObjectPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;

private:
	MonoObject* Object_New(void* InAddress) const;

	MonoClass* Class;

	MonoProperty* Property;
};
