#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FPrimitivePropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit FPrimitivePropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool IsPrimitiveProperty() const override;

private:
	MonoClass* Class;
};
