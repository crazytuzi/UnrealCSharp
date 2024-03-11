#include "Reflection/Property/PrimitiveProperty/FBoolPropertyDescriptor.h"

void FBoolPropertyDescriptor::Set(void* Src, void* Dest) const
{
	BoolProperty->SetPropertyValue(Dest, *((bool*)Src));
}
