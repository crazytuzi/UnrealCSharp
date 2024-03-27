﻿#pragma once

#include "Reflection/Property/FCompoundPropertyDescriptor.h"
#include "mono/metadata/object-forward.h"

class FNamePropertyDescriptor final : public FCompoundPropertyDescriptor
{
public:
	explicit FNamePropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

public:
	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const override;

private:
	MonoObject* Object_New(void* InAddress) const;
};
