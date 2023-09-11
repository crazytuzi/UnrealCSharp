﻿#include "Reflection/Property/FPropertyDescriptor.h"
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

EPropertyTypeExtent FPropertyDescriptor::GetPropertyType(const FProperty* Property)
{
	if (Property != nullptr)
	{
		GET_PROPERTY_TYPE(FByteProperty, EPropertyTypeExtent::Byte)

		GET_PROPERTY_TYPE(FUInt16Property, EPropertyTypeExtent::UInt16)

		GET_PROPERTY_TYPE(FUInt32Property, EPropertyTypeExtent::UInt32)

		GET_PROPERTY_TYPE(FUInt64Property, EPropertyTypeExtent::UInt64)

		GET_PROPERTY_TYPE(FInt8Property, EPropertyTypeExtent::Int8)

		GET_PROPERTY_TYPE(FInt16Property, EPropertyTypeExtent::Int16)

		GET_PROPERTY_TYPE(FIntProperty, EPropertyTypeExtent::Int)

		GET_PROPERTY_TYPE(FInt64Property, EPropertyTypeExtent::Int64)

		GET_PROPERTY_TYPE(FBoolProperty, EPropertyTypeExtent::Bool)

		GET_PROPERTY_TYPE(FFloatProperty, EPropertyTypeExtent::Float)

		GET_PROPERTY_TYPE(FClassProperty, EPropertyTypeExtent::ClassReference)

		GET_PROPERTY_TYPE(FObjectProperty, EPropertyTypeExtent::ObjectReference)

		GET_PROPERTY_TYPE(FNameProperty, EPropertyTypeExtent::Name)

		GET_PROPERTY_TYPE(FDelegateProperty, EPropertyTypeExtent::Delegate)

		GET_PROPERTY_TYPE(FInterfaceProperty, EPropertyTypeExtent::Interface)

		GET_PROPERTY_TYPE(FStructProperty, EPropertyTypeExtent::Struct)

		GET_PROPERTY_TYPE(FArrayProperty, EPropertyTypeExtent::Array)

		GET_PROPERTY_TYPE(FEnumProperty, EPropertyTypeExtent::Enum)

		GET_PROPERTY_TYPE(FStrProperty, EPropertyTypeExtent::String)

		GET_PROPERTY_TYPE(FTextProperty, EPropertyTypeExtent::Text)

		GET_PROPERTY_TYPE(FMulticastInlineDelegateProperty, EPropertyTypeExtent::MulticastInlineDelegate)

		GET_PROPERTY_TYPE(FMulticastSparseDelegateProperty, EPropertyTypeExtent::MulticastSparseDelegate)

		GET_PROPERTY_TYPE(FMulticastDelegateProperty, EPropertyTypeExtent::MulticastDelegate)

		GET_PROPERTY_TYPE(FWeakObjectProperty, EPropertyTypeExtent::WeakObjectReference)

		GET_PROPERTY_TYPE(FLazyObjectProperty, EPropertyTypeExtent::LazyObjectReference)

		GET_PROPERTY_TYPE(FSoftClassProperty, EPropertyTypeExtent::SoftClassReference)

		GET_PROPERTY_TYPE(FSoftObjectProperty, EPropertyTypeExtent::SoftObjectReference)

		GET_PROPERTY_TYPE(FDoubleProperty, EPropertyTypeExtent::Double)

		GET_PROPERTY_TYPE(FMapProperty, EPropertyTypeExtent::Map)

		GET_PROPERTY_TYPE(FSetProperty, EPropertyTypeExtent::Set)

		GET_PROPERTY_TYPE(FFieldPathProperty, EPropertyTypeExtent::FieldPath)
	}

	return EPropertyTypeExtent::None;
}

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

	NEW_PROPERTY_DESCRIPTOR(FClassProperty)

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

	return nullptr;
}

FPropertyDescriptor::FPropertyDescriptor(FProperty* InProperty):
	Property(InProperty)
{
}

void FPropertyDescriptor::Get(void* Src, void** Dest) const
{
}

void FPropertyDescriptor::Get(void* Src, void* Dest) const
{
	Get(Src, static_cast<void**>(Dest));
}

void FPropertyDescriptor::Set(void* Src, void* Dest) const
{
}

bool FPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	return Property != nullptr ? Property->Identical(A, B, PortFlags) : false;
}

void FPropertyDescriptor::DestroyValue(void* Dest) const
{
	if (Property != nullptr)
	{
		Property->DestroyValue(Dest);
	}
}

bool FPropertyDescriptor::IsPrimitiveProperty() const
{
	return false;
}
