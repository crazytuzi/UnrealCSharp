#include "Reflection/Property/PrimitiveProperty/FUInt32PropertyDescriptor.h"

void FUInt32PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (uint64)(*((uint32*)Src)));
}
