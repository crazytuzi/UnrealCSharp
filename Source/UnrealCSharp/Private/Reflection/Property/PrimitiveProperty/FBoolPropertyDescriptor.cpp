#include "Reflection/Property/PrimitiveProperty/FBoolPropertyDescriptor.h"

void FBoolPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->SetPropertyValue(Dest, *static_cast<bool*>(Src));
	}
}
