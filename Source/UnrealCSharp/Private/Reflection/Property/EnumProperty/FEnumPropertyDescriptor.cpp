#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Domain/Script/IManagedHandle.h"

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*Dest = IManagedHandleToObject(Class->BoxValue(Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*Dest = IManagedHandleToObject(Class->BoxValue(Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void* Dest) const
{
	Property->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
}

void FEnumPropertyDescriptor::Set(void* Src, void* Dest) const
{
	Property->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
}

void FEnumPropertyDescriptor::DestroyValue(void* Dest) const
{
}
