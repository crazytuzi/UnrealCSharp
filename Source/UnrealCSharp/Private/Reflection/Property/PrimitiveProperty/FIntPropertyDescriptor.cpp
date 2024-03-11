#include "Reflection/Property/PrimitiveProperty/FIntPropertyDescriptor.h"

void FIntPropertyDescriptor::Set(void* Src, void* Dest) const
{
	NumericProperty->SetIntPropertyValue(Dest, (int64) (*((int32*)Src)));
}
