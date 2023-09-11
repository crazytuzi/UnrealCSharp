﻿#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "mono/metadata/details/object-types.h"

class FMulticastDelegatePropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit FMulticastDelegatePropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

protected:
	virtual const FMulticastScriptDelegate* GetMulticastDelegate(void* InAddress) const;

private:
	MonoObject* Object_New(void* InAddress) const;

	MonoClass* Class;

	MonoReflectionType* Type;
};
