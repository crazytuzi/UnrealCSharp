#pragma once

#include "mono/metadata/object.h"

class FContainerHelper
{
public:
	static FProperty* Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner, const FName& InName,
	                          const EObjectFlags InObjectFlags);

private:
	static FProperty* ManagedFactory(EPropertyType InPropertyType, MonoReflectionType* InReflectionType,
	                                 const FFieldVariant& InOwner, const FName& InName,
	                                 const EObjectFlags InObjectFlags);
};
