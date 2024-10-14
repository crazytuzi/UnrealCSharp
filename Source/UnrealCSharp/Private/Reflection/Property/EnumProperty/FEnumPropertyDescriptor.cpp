#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Class, Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Class, Src));
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
