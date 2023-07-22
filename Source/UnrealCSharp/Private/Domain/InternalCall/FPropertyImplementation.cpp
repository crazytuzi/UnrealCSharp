#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterProperty
{
	FRegisterProperty()
	{
		FClassBuilder(TEXT("Property"), NAMESPACE_LIBRARY)
			.Function("GetObjectByteProperty", FPropertyImplementation::Property_GetObjectBytePropertyImplementation)
			.Function("SetObjectByteProperty", FPropertyImplementation::Property_SetObjectBytePropertyImplementation)
			.Function("GetObjectUInt16Property",
			          FPropertyImplementation::Property_GetObjectUInt16PropertyImplementation)
			.Function("SetObjectUInt16Property",
			          FPropertyImplementation::Property_SetObjectUInt16PropertyImplementation)
			.Function("GetObjectUInt32Property",
			          FPropertyImplementation::Property_GetObjectUInt32PropertyImplementation)
			.Function("SetObjectUInt32Property",
			          FPropertyImplementation::Property_SetObjectUInt32PropertyImplementation)
			.Function("GetObjectUInt64Property",
			          FPropertyImplementation::Property_GetObjectUInt64PropertyImplementation)
			.Function("SetObjectUInt64Property",
			          FPropertyImplementation::Property_SetObjectUInt64PropertyImplementation)
			.Function("GetObjectInt8Property", FPropertyImplementation::Property_GetObjectInt8PropertyImplementation)
			.Function("SetObjectInt8Property", FPropertyImplementation::Property_SetObjectInt8PropertyImplementation)
			.Function("GetObjectInt16Property", FPropertyImplementation::Property_GetObjectInt16PropertyImplementation)
			.Function("SetObjectInt16Property", FPropertyImplementation::Property_SetObjectInt16PropertyImplementation)
			.Function("GetObjectIntProperty", FPropertyImplementation::Property_GetObjectIntPropertyImplementation)
			.Function("SetObjectIntProperty", FPropertyImplementation::Property_SetObjectIntPropertyImplementation)
			.Function("GetObjectInt64Property", FPropertyImplementation::Property_GetObjectInt64PropertyImplementation)
			.Function("SetObjectInt64Property", FPropertyImplementation::Property_SetObjectInt64PropertyImplementation)
			.Function("GetObjectBoolProperty", FPropertyImplementation::Property_GetObjectBoolPropertyImplementation)
			.Function("SetObjectBoolProperty", FPropertyImplementation::Property_SetObjectBoolPropertyImplementation)
			.Function("GetObjectFloatProperty", FPropertyImplementation::Property_GetObjectFloatPropertyImplementation)
			.Function("SetObjectFloatProperty", FPropertyImplementation::Property_SetObjectFloatPropertyImplementation)
			.Function("GetObjectObjectProperty",
			          FPropertyImplementation::Property_GetObjectObjectPropertyImplementation)
			.Function("SetObjectObjectProperty",
			          FPropertyImplementation::Property_SetObjectObjectPropertyImplementation)
			.Function("GetObjectClassProperty", FPropertyImplementation::Property_GetObjectClassPropertyImplementation)
			.Function("SetObjectClassProperty", FPropertyImplementation::Property_SetObjectClassPropertyImplementation)
			.Function("GetObjectInterfaceProperty",
			          FPropertyImplementation::Property_GetObjectInterfacePropertyImplementation)
			.Function("SetObjectInterfaceProperty",
			          FPropertyImplementation::Property_SetObjectInterfacePropertyImplementation)
			.Function("GetObjectArrayProperty", FPropertyImplementation::Property_GetObjectArrayPropertyImplementation)
			.Function("SetObjectArrayProperty", FPropertyImplementation::Property_SetObjectArrayPropertyImplementation)
			.Function("GetObjectWeakObjectProperty",
			          FPropertyImplementation::Property_GetObjectWeakObjectPropertyImplementation)
			.Function("SetObjectWeakObjectProperty",
			          FPropertyImplementation::Property_SetObjectWeakObjectPropertyImplementation)
			.Function("GetObjectLazyObjectProperty",
			          FPropertyImplementation::Property_GetObjectLazyObjectPropertyImplementation)
			.Function("SetObjectLazyObjectProperty",
			          FPropertyImplementation::Property_SetObjectLazyObjectPropertyImplementation)
			.Function("GetObjectSoftClassProperty",
			          FPropertyImplementation::Property_GetObjectSoftClassPropertyImplementation)
			.Function("SetObjectSoftClassProperty",
			          FPropertyImplementation::Property_SetObjectSoftClassPropertyImplementation)
			.Function("GetObjectSoftObjectProperty",
			          FPropertyImplementation::Property_GetObjectSoftObjectPropertyImplementation)
			.Function("SetObjectSoftObjectProperty",
			          FPropertyImplementation::Property_SetObjectSoftObjectPropertyImplementation)
			.Function("GetObjectDoubleProperty",
			          FPropertyImplementation::Property_GetObjectDoublePropertyImplementation)
			.Function("SetObjectDoubleProperty",
			          FPropertyImplementation::Property_SetObjectDoublePropertyImplementation)
			.Function("GetObjectMapProperty", FPropertyImplementation::Property_GetObjectMapPropertyImplementation)
			.Function("SetObjectMapProperty", FPropertyImplementation::Property_SetObjectMapPropertyImplementation)
			.Function("GetObjectSetProperty", FPropertyImplementation::Property_GetObjectSetPropertyImplementation)
			.Function("SetObjectSetProperty", FPropertyImplementation::Property_SetObjectSetPropertyImplementation)
			.Function("GetObjectFieldPathProperty",
			          FPropertyImplementation::Property_GetObjectFieldPathPropertyImplementation)
			.Function("SetObjectFieldPathProperty",
			          FPropertyImplementation::Property_SetObjectFieldPathPropertyImplementation)
			.Function("GetStructByteProperty", FPropertyImplementation::Property_GetStructBytePropertyImplementation)
			.Function("SetStructByteProperty", FPropertyImplementation::Property_SetStructBytePropertyImplementation)
			.Function("GetStructUInt16Property",
			          FPropertyImplementation::Property_GetStructUInt16PropertyImplementation)
			.Function("SetStructUInt16Property",
			          FPropertyImplementation::Property_SetStructUInt16PropertyImplementation)
			.Function("GetStructUInt32Property",
			          FPropertyImplementation::Property_GetStructUInt32PropertyImplementation)
			.Function("SetStructUInt32Property",
			          FPropertyImplementation::Property_SetStructUInt32PropertyImplementation)
			.Function("GetStructUInt64Property",
			          FPropertyImplementation::Property_GetStructUInt64PropertyImplementation)
			.Function("SetStructUInt64Property",
			          FPropertyImplementation::Property_SetStructUInt64PropertyImplementation)
			.Function("GetStructInt8Property", FPropertyImplementation::Property_GetStructInt8PropertyImplementation)
			.Function("SetStructInt8Property", FPropertyImplementation::Property_SetStructInt8PropertyImplementation)
			.Function("GetStructInt16Property", FPropertyImplementation::Property_GetStructInt16PropertyImplementation)
			.Function("SetStructInt16Property", FPropertyImplementation::Property_SetStructInt16PropertyImplementation)
			.Function("GetStructIntProperty", FPropertyImplementation::Property_GetStructIntPropertyImplementation)
			.Function("SetStructIntProperty", FPropertyImplementation::Property_SetStructIntPropertyImplementation)
			.Function("GetStructInt64Property", FPropertyImplementation::Property_GetStructInt64PropertyImplementation)
			.Function("SetStructInt64Property", FPropertyImplementation::Property_SetStructInt64PropertyImplementation)
			.Function("GetStructBoolProperty", FPropertyImplementation::Property_GetStructBoolPropertyImplementation)
			.Function("SetStructBoolProperty", FPropertyImplementation::Property_SetStructBoolPropertyImplementation)
			.Function("GetStructFloatProperty", FPropertyImplementation::Property_GetStructFloatPropertyImplementation)
			.Function("SetStructFloatProperty", FPropertyImplementation::Property_SetStructFloatPropertyImplementation)
			.Function("GetStructObjectProperty",
			          FPropertyImplementation::Property_GetStructObjectPropertyImplementation)
			.Function("SetStructObjectProperty",
			          FPropertyImplementation::Property_SetStructObjectPropertyImplementation)
			.Function("GetStructClassProperty", FPropertyImplementation::Property_GetStructClassPropertyImplementation)
			.Function("SetStructClassProperty", FPropertyImplementation::Property_SetStructClassPropertyImplementation)
			.Function("GetStructInterfaceProperty",
			          FPropertyImplementation::Property_GetStructInterfacePropertyImplementation)
			.Function("SetStructInterfaceProperty",
			          FPropertyImplementation::Property_SetStructInterfacePropertyImplementation)
			.Function("GetStructArrayProperty", FPropertyImplementation::Property_GetStructArrayPropertyImplementation)
			.Function("SetStructArrayProperty", FPropertyImplementation::Property_SetStructArrayPropertyImplementation)
			.Function("GetStructWeakObjectProperty",
			          FPropertyImplementation::Property_GetStructWeakObjectPropertyImplementation)
			.Function("SetStructWeakObjectProperty",
			          FPropertyImplementation::Property_SetStructWeakObjectPropertyImplementation)
			.Function("GetStructLazyObjectProperty",
			          FPropertyImplementation::Property_GetStructLazyObjectPropertyImplementation)
			.Function("SetStructLazyObjectProperty",
			          FPropertyImplementation::Property_SetStructLazyObjectPropertyImplementation)
			.Function("GetStructSoftClassProperty",
			          FPropertyImplementation::Property_GetStructSoftClassPropertyImplementation)
			.Function("SetStructSoftClassProperty",
			          FPropertyImplementation::Property_SetStructSoftClassPropertyImplementation)
			.Function("GetStructSoftObjectProperty",
			          FPropertyImplementation::Property_GetStructSoftObjectPropertyImplementation)
			.Function("SetStructSoftObjectProperty",
			          FPropertyImplementation::Property_SetStructSoftObjectPropertyImplementation)
			.Function("GetStructDoubleProperty",
			          FPropertyImplementation::Property_GetStructDoublePropertyImplementation)
			.Function("SetStructDoubleProperty",
			          FPropertyImplementation::Property_SetStructDoublePropertyImplementation)
			.Function("GetStructMapProperty", FPropertyImplementation::Property_GetStructMapPropertyImplementation)
			.Function("SetStructMapProperty", FPropertyImplementation::Property_SetStructMapPropertyImplementation)
			.Function("GetStructSetProperty", FPropertyImplementation::Property_GetStructSetPropertyImplementation)
			.Function("SetStructSetProperty", FPropertyImplementation::Property_SetStructSetPropertyImplementation)
			.Function("GetStructFieldPathProperty",
			          FPropertyImplementation::Property_GetStructFieldPathPropertyImplementation)
			.Function("SetStructFieldPathProperty",
			          FPropertyImplementation::Property_SetStructFieldPathPropertyImplementation)
			.Register();
	}
};

static FRegisterProperty RegisterProperty;

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int8, int8)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int, int32)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Bool, bool)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Float, float)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Object, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Class, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Interface, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Array, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(WeakObject, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(LazyObject, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(SoftClass, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(SoftObject, MonoObject)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Map, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Set, MonoObject)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(FieldPath, MonoObject)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int8, int8)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int, int32)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Bool, bool)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Float, float)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Object, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Class, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Interface, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Array, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(WeakObject, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(LazyObject, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(SoftClass, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(SoftObject, MonoObject)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Map, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Set, MonoObject)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(FieldPath, MonoObject)
