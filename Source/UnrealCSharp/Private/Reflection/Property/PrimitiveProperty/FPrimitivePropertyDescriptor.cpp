#include "Reflection/Property/PrimitiveProperty/FPrimitivePropertyDescriptor.h"

void FPrimitivePropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->CopySingleValue(Dest, Src);
	}
}

void FPrimitivePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->CopySingleValue(Dest, Src);
	}
}

bool FPrimitivePropertyDescriptor::IsPrimitiveProperty() const
{
	return true;
}
