#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"

void FEnumPropertyDescriptor::Get(void* Src, void** Dest) const
{
	*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
		FTypeBridge::GetMonoClass(Property), Src));
}

void FEnumPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (EnumProperty != nullptr)
	{
		EnumProperty->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (EnumProperty != nullptr)
	{
		EnumProperty->GetUnderlyingProperty()->CopySingleValue(Dest, Src);
	}
}

void FEnumPropertyDescriptor::DestroyValue(void* Dest) const
{
}

bool FEnumPropertyDescriptor::IsPrimitiveProperty() const
{
	return true;
}
