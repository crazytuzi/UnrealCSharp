#include "Reflection/Property/PrimitiveProperty/FBoolPropertyDescriptor.h"

void FBoolPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (BoolProperty != nullptr)
	{
		BoolProperty->SetPropertyValue(Dest, *((bool*)Src));
	}
}
