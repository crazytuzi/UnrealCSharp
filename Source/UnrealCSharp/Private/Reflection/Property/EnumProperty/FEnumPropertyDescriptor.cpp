#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FEnumPropertyDescriptor::Get(void* Src, void** Dest, bool bIsCopy) const
{
	*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Class, Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::DestroyValue(void* Dest) const
{
}
