#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"
#include "mono/metadata/details/class-types.h"

class FCompoundPropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit FCompoundPropertyDescriptor(FProperty* InProperty);

protected:
	FGarbageCollectionHandle MonoObject2GarbageCollectionHandle(MonoObject* InMonoObject) const;

protected:
	MonoClass* Class;

private:
	MonoProperty* Property;
};
