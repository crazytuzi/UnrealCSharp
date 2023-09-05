#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FEnumPropertyDescriptor final : public FPropertyDescriptor
{
public:
	explicit FEnumPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Get(void* Src, void* Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual void DestroyValue(void* Dest) const override;

	virtual bool IsPrimitiveProperty() const override;

private:
	MonoClass* Class;
};
