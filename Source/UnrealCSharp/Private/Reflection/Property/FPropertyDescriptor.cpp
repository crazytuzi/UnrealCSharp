#include "Reflection/Property/FPropertyDescriptor.h"
#include "Macro/PropertyMacro.h"
#include "Reflection/Property/PrimitiveProperty/FBytePropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FUInt16PropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FUInt32PropertyDescriptor.h"
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
#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Reflection/Property/PrimitiveProperty/FDoublePropertyDescriptor.h"
#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"

int32 GetPropertyType(const FProperty* Property)
{
	if (Property != nullptr)
	{
		GET_PROPERTY_TYPE(FByteProperty, CPT_Byte)

		GET_PROPERTY_TYPE(FUInt16Property, CPT_UInt16)

		GET_PROPERTY_TYPE(FUInt32Property, CPT_UInt32)

		GET_PROPERTY_TYPE(FInt8Property, CPT_Int8)

		GET_PROPERTY_TYPE(FInt16Property, CPT_Int16)

		GET_PROPERTY_TYPE(FIntProperty, CPT_Int)

		GET_PROPERTY_TYPE(FInt64Property, CPT_Int64)

		GET_PROPERTY_TYPE(FBoolProperty, CPT_Bool)

		GET_PROPERTY_TYPE(FFloatProperty, CPT_Float)

		GET_PROPERTY_TYPE(FClassProperty, CPT_ObjectReference)

		GET_PROPERTY_TYPE(FObjectProperty, CPT_ObjectReference)

		GET_PROPERTY_TYPE(FNameProperty, CPT_Name)

		GET_PROPERTY_TYPE(FDelegateProperty, CPT_Delegate)

		GET_PROPERTY_TYPE(FInterfaceProperty, CPT_Interface)

		GET_PROPERTY_TYPE(FStructProperty, CPT_Struct)

		GET_PROPERTY_TYPE(FArrayProperty, CPT_Array)

		GET_PROPERTY_TYPE(FEnumProperty, CPT_Enum)

		GET_PROPERTY_TYPE(FStrProperty, CPT_String)

		GET_PROPERTY_TYPE(FTextProperty, CPT_Text)

		GET_PROPERTY_TYPE(FMulticastDelegateProperty, CPT_MulticastDelegate)

		GET_PROPERTY_TYPE(FMulticastInlineDelegateProperty, CPT_MulticastDelegate)

		GET_PROPERTY_TYPE(FMulticastSparseDelegateProperty, CPT_MulticastDelegate)

		GET_PROPERTY_TYPE(FWeakObjectProperty, CPT_WeakObjectReference)

		GET_PROPERTY_TYPE(FLazyObjectProperty, CPT_LazyObjectReference)

		GET_PROPERTY_TYPE(FSoftObjectProperty, CPT_SoftObjectReference)

		GET_PROPERTY_TYPE(FDoubleProperty, CPT_Double)

		GET_PROPERTY_TYPE(FMapProperty, CPT_Map)

		GET_PROPERTY_TYPE(FSetProperty, CPT_Set)
	}

	return CPT_None;
}

FPropertyDescriptor* FPropertyDescriptor::Factory(FProperty* InProperty)
{
	NEW_PROPERTY_DESCRIPTOR(FByteProperty)

	NEW_PROPERTY_DESCRIPTOR(FUInt16Property)

	NEW_PROPERTY_DESCRIPTOR(FUInt32Property)

	NEW_PROPERTY_DESCRIPTOR(FInt8Property)

	NEW_PROPERTY_DESCRIPTOR(FInt16Property)

	NEW_PROPERTY_DESCRIPTOR(FIntProperty)

	NEW_PROPERTY_DESCRIPTOR(FInt64Property)

	NEW_PROPERTY_DESCRIPTOR(FBoolProperty)

	NEW_PROPERTY_DESCRIPTOR(FFloatProperty)

	NEW_PROPERTY_DESCRIPTOR(FObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FClassProperty)

	NEW_PROPERTY_DESCRIPTOR(FNameProperty)

	NEW_PROPERTY_DESCRIPTOR(FDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FInterfaceProperty)

	NEW_PROPERTY_DESCRIPTOR(FStructProperty)

	NEW_PROPERTY_DESCRIPTOR(FArrayProperty)

	NEW_PROPERTY_DESCRIPTOR(FEnumProperty)

	NEW_PROPERTY_DESCRIPTOR(FStrProperty)

	NEW_PROPERTY_DESCRIPTOR(FTextProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastInlineDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FMulticastSparseDelegateProperty)

	NEW_PROPERTY_DESCRIPTOR(FWeakObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FLazyObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FSoftObjectProperty)

	NEW_PROPERTY_DESCRIPTOR(FDoubleProperty)

	NEW_PROPERTY_DESCRIPTOR(FMapProperty)

	NEW_PROPERTY_DESCRIPTOR(FSetProperty)

	return nullptr;
}

FPropertyDescriptor::FPropertyDescriptor(FProperty* InProperty):
	Property(InProperty)
{
}

void FPropertyDescriptor::Get(void* Src, void** Dest) const
{
	*Dest = Src;
}

void FPropertyDescriptor::Get(void* Src, void* Dest) const
{
}

void FPropertyDescriptor::Set(void* Src, void* Dest) const
{
}

FProperty* FPropertyDescriptor::GetProperty() const
{
	return Property;
}

bool FPropertyDescriptor::IsPrimitiveProperty() const
{
	return false;
}
