﻿#pragma once

#include "FContainerPropertyDescriptor.h"
#include "mono/metadata/details/object-types.h"

class FMapPropertyDescriptor final : public FContainerPropertyDescriptor
{
public:
	explicit FMapPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const override;

	virtual void Set(void* Src, void* Dest) const override;

private:
	MonoObject* Object_New(void* InAddress) const;

	MonoClass* Class;

	MonoReflectionType* KeyType;

	MonoReflectionType* ValueType;
};
