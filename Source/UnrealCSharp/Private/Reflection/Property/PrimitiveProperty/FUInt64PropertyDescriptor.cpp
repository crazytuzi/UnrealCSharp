#include "Reflection/Property/PrimitiveProperty/FUInt64PropertyDescriptor.h"

void FUInt64PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, *((uint64*)Src));
}
