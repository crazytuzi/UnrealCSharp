#include "Reflection/Property/PrimitiveProperty/FInt8PropertyDescriptor.h"

void FInt8PropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (int64)(*((int8*)Src)));
}