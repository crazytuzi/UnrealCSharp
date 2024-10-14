#include "Reflection/Property/FPropertyDescriptor.h"
#include "Macro/PropertyMacro.h"
#include "Reflection/Property/PrimitiveProperty/FBytePropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FUInt16PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FUInt32PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FUInt64PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FInt8PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FInt16PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FIntPropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FInt64PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FBoolPropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FFloatPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FSubclassOfPropertyDescriptor.h"
#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Reflection/Property/EnumProperty/FEnumPropertyDescriptor.h"
#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Reflection/Property/DelegateProperty/FMulticastInlineDelegatePropertyDescriptor.h"
#include "Reflection/Property/DelegateProperty/FMulticastSparseDelegatePropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FLazyObjectPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FSoftClassPropertyDescriptor.h"
#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FDoublePropertyDescriptor.h"
#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Reflection/Property/FieldPathProperty/FFieldPathPropertyDescriptor.h"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#include "Reflection/Property/OptionalProperty/FOptionalPropertyDescriptor.h"
#endif

FPropertyDescriptor* FPropertyDescriptor::Factory(FProperty* InProperty)
{
	NEW_PROPERTY_DESCRIPTOR(FByteProperty)

	NEW_PROPERTY_DESCRIPTOR(FUInt16Property)

	NEW_PROPERTY_DESCRIPTOR(FUInt32Property)

	NEW_PROPERTY_DESCRIPTOR(FUInt64Property)

	NEW_PROPERTY_DESCRIPTOR(FInt8Property)

	NEW_PROPERTY_DESCRIPTOR(FInt16Property)

	NEW_PROPERTY_DESCRIPTOR(FIntProperty)

	NEW_PROPERTY_DESCRIPTOR(FInt64Property)

	NEW_PROPERTY_DESCRIPTOR(FBoolProperty)

	NEW_PROPERTY_DESCRIPTOR(FFloatProperty)

	if (const auto Property = CastField<FClassProperty>(InProperty))
	{
		if (Property->HasAnyPropertyFlags(CPF_UObjectWrapper))
		{
			return new FSubclassOfPropertyDescriptor(Property);
		}
		else
		{
			return new FClassPropertyDescriptor(Property);
		}
	}

	NEW_PROPERTY_DESCRIPTOR(FObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FNameProperty)

	NEW_PROPERTY_DESCRIPTOR(FDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FInterfaceProperty)

	NEW_PROPERTY_DESCRIPTOR(FStructProperty)

	NEW_PROPERTY_DESCRIPTOR(FArrayProperty)

	NEW_PROPERTY_DESCRIPTOR(FEnumProperty)

	NEW_PROPERTY_DESCRIPTOR(FStrProperty)

	NEW_PROPERTY_DESCRIPTOR(FTextProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastInlineDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastSparseDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FWeakObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FLazyObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FSoftClassProperty)

	NEW_PROPERTY_DESCRIPTOR(FSoftObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FDoubleProperty)

	NEW_PROPERTY_DESCRIPTOR(FMapProperty)

	NEW_PROPERTY_DESCRIPTOR(FSetProperty)

	NEW_PROPERTY_DESCRIPTOR(FFieldPathProperty)

#if UE_F_OPTIONAL_PROPERTY
	NEW_PROPERTY_DESCRIPTOR(FOptionalProperty)
#endif

	return nullptr;
}

void FPropertyDescriptor::Get(void* Src, void** Dest) const
{
}

void FPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
}

void FPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
}

void FPropertyDescriptor::Get(void* Src, void* Dest) const
{
}

void FPropertyDescriptor::Set(void* Src, void* Dest) const
{
}

FProperty* FPropertyDescriptor::GetProperty() const
{
	return nullptr;
}

void* FPropertyDescriptor::CopyValue(const void* InAddress) const
{
	return nullptr;
}

void FPropertyDescriptor::DestroyProperty()
{
}

bool FPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto Property = GetProperty())
	{
		return Property->Identical(A, B, PortFlags);
	}

	return false;
}

void FPropertyDescriptor::DestroyValue(void* Dest) const
{
	if (const auto Property = GetProperty())
	{
		Property->DestroyValue(Dest);
	}
}

bool FPropertyDescriptor::IsPrimitiveProperty() const
{
	return false;
}
