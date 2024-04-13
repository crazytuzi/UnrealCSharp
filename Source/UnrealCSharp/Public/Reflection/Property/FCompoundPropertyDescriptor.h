#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "mono/metadata/details/object-types.h"

class FCompoundPropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit FCompoundPropertyDescriptor(FProperty* InProperty);

protected:
	MonoClass* Class;
};
