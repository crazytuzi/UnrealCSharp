#include "Reflection/Property/FCompoundPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"

FCompoundPropertyDescriptor::FCompoundPropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(FTypeBridge::GetMonoClass(InProperty))
{
}
