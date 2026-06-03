#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Domain/Script/IManagedHandle.h"

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*Dest = MANAGED_HANDLE_TO_OBJECT(Class->BoxValue(Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*Dest = MANAGED_HANDLE_TO_OBJECT(Class->BoxValue(Src));
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
