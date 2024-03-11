#include "Reflection/Property/PrimitiveProperty/FInt16PropertyDescriptor.h"

void FInt16PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (int64)(*((int16*)Src)));
}
