#include "Reflection/Property/PrimitiveProperty/FPrimitivePropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"

void FPrimitivePropertyDescriptor::Get(void* Src, void** Dest) const
{
	*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
		FTypeBridge::GetMonoClass(Property), Src));
}

void FPrimitivePropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->CopySingleValue(Dest, Src);
	}
}

void FPrimitivePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		Property->InitializeValue(Dest);

		Property->CopySingleValue(Dest, Src);
	}
}

bool FPrimitivePropertyDescriptor::IsPrimitiveProperty() const
{
	return true;
}
