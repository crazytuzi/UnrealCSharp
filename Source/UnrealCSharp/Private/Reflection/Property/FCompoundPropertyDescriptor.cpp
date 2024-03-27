#include "Reflection/Property/FCompoundPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "CoreMacro/PropertyMacro.h"
#include "Domain/FMonoDomain.h"

FCompoundPropertyDescriptor::FCompoundPropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(FTypeBridge::GetMonoClass(InProperty)),
	Property(FMonoDomain::Class_Get_Property_From_Name(Class, PROPERTY_GARBAGE_COLLECTION_HANDLE))
{
}

FGarbageCollectionHandle FCompoundPropertyDescriptor::MonoObject2GarbageCollectionHandle(MonoObject* InMonoObject) const
{
	return FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(InMonoObject, Property);
}
