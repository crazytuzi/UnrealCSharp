#pragma once

#include "Bridge/EPropertyTypeExtent.h"
#include "mono/metadata/object.h"

class FContainerHelper
{
public:
	static FProperty* Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner, const FName& InName,
	                          const EObjectFlags InObjectFlags);

private:
	static FProperty* ManagedFactory(EPropertyTypeExtent InPropertyType, MonoReflectionType* InReflectionType,
	                                 const FFieldVariant& InOwner, const FName& InName,
	                                 const EObjectFlags InObjectFlags);

	// @TODO
	static FString GetPathName(MonoReflectionType* InReflectionType);

	static FString GetGenericPathName(MonoReflectionType* InReflectionType);
};
