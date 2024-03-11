#include "Reflection/Property/PrimitiveProperty/FUInt16PropertyDescriptor.h"

void FUInt16PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (uint64)(*((uint16*)Src)));
}
