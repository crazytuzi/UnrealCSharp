#include "Reflection/Property/PrimitiveProperty/FBytePropertyDescriptor.h"

void FBytePropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (uint64) (*((uint8*)Src)));
}
