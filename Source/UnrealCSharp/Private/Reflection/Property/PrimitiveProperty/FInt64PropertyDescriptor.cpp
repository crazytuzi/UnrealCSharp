#include "Reflection/Property/PrimitiveProperty/FInt64PropertyDescriptor.h"

void FInt64PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, *((int64*)Src));
}
