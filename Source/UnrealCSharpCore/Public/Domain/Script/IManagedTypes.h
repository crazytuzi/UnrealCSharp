#pragma once

#include "CoreMinimal.h"
#if WITH_MONO
#include "mono/metadata/object.h"
#include "mono/metadata/class.h"
#endif
#include "Domain/Script/IManagedHandle.h"

#if WITH_MONO
#define MANAGED_TYPE(Type) using IManaged##Type = Mono##Type*; \
FORCEINLINE IManaged##Type IManagedHandleToIManaged##Type(const IManagedHandle InManagedHandle) \
{ \
	return MANAGED_HANDLE_CAST_TO_OBJECT(IManaged##Type, InManagedHandle); \
}
#else
#define MANAGED_TYPE(Type) using IManaged##Type = TManaged<struct IManaged##Type##Tag>; \
FORCEINLINE IManaged##Type IManagedHandleToIManaged##Type(const IManagedHandle InManagedHandle) \
{ \
	return IManaged##Type{InManagedHandle.Value}; \
}
#endif

MANAGED_TYPE(Object)

MANAGED_TYPE(Class)

MANAGED_TYPE(Type)

MANAGED_TYPE(VTable)

MANAGED_TYPE(Method)

MANAGED_TYPE(Property)

MANAGED_TYPE(ClassField)

MANAGED_TYPE(ReflectionType)

MANAGED_TYPE(ReflectionMethod)

MANAGED_TYPE(ReflectionProperty)

MANAGED_TYPE(ReflectionField)

MANAGED_TYPE(Array)

MANAGED_TYPE(String)

MANAGED_TYPE(Assembly)

MANAGED_TYPE(AssemblyName)

MANAGED_TYPE(ReflectionAssembly)

MANAGED_TYPE(Image)

#if WITH_MONO
#define INVALID_MANAGED nullptr
#else
#define INVALID_MANAGED IManagedNull{}
#endif

template <typename T>
FORCEINLINE bool IManagedIsValid(T InManaged)
{
	return InManaged != INVALID_MANAGED;
}
