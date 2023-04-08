#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"

void FEnumPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (EnumProperty != nullptr)
	{
		EnumProperty->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (EnumProperty != nullptr)
	{
		EnumProperty->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::DestroyValue(void* Dest) const
{
}

bool FEnumPropertyDescriptor::IsPrimitiveProperty() const
{
	return true;
}
