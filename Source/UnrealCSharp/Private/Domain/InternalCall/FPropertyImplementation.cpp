#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterProperty
{
	FRegisterProperty()
	{
		FBindingClassBuilder(TEXT("Property"), NAMESPACE_LIBRARY)
			.Function("GetObjectByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectBytePropertyImplementation))
			.Function("SetObjectByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectBytePropertyImplementation))
			.Function("GetObjectUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectUInt16PropertyImplementation))
			.Function("SetObjectUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectUInt16PropertyImplementation))
			.Function("GetObjectUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectUInt32PropertyImplementation))
			.Function("SetObjectUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectUInt32PropertyImplementation))
			.Function("GetObjectUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectUInt64PropertyImplementation))
			.Function("SetObjectUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectUInt64PropertyImplementation))
			.Function("GetObjectInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectInt8PropertyImplementation))
			.Function("SetObjectInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectInt8PropertyImplementation))
			.Function("GetObjectInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectInt16PropertyImplementation))
			.Function("SetObjectInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectInt16PropertyImplementation))
			.Function("GetObjectIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectIntPropertyImplementation))
			.Function("SetObjectIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectIntPropertyImplementation))
			.Function("GetObjectInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectInt64PropertyImplementation))
			.Function("SetObjectInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectInt64PropertyImplementation))
			.Function("GetObjectBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectBoolPropertyImplementation))
			.Function("SetObjectBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectBoolPropertyImplementation))
			.Function("GetObjectFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectFloatPropertyImplementation))
			.Function("SetObjectFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectFloatPropertyImplementation))
			.Function("GetObjectObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectObjectPropertyImplementation))
			.Function("SetObjectObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectObjectPropertyImplementation))
			.Function("GetObjectClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectClassPropertyImplementation))
			.Function("SetObjectClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectClassPropertyImplementation))
			.Function("GetObjectInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectInterfacePropertyImplementation))
			.Function("SetObjectInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectInterfacePropertyImplementation))
			.Function("GetObjectArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectArrayPropertyImplementation))
			.Function("SetObjectArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectArrayPropertyImplementation))
			.Function("GetObjectWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectWeakObjectPropertyImplementation))
			.Function("SetObjectWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectWeakObjectPropertyImplementation))
			.Function("GetObjectLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectLazyObjectPropertyImplementation))
			.Function("SetObjectLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectLazyObjectPropertyImplementation))
			.Function("GetObjectSoftClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectSoftClassPropertyImplementation))
			.Function("SetObjectSoftClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectSoftClassPropertyImplementation))
			.Function("GetObjectSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectSoftObjectPropertyImplementation))
			.Function("SetObjectSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectSoftObjectPropertyImplementation))
			.Function("GetObjectDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectDoublePropertyImplementation))
			.Function("SetObjectDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectDoublePropertyImplementation))
			.Function("GetObjectMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectMapPropertyImplementation))
			.Function("SetObjectMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectMapPropertyImplementation))
			.Function("GetObjectSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectSetPropertyImplementation))
			.Function("SetObjectSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectSetPropertyImplementation))
			.Function("GetObjectFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectFieldPathPropertyImplementation))
			.Function("SetObjectFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectFieldPathPropertyImplementation))
			.Function("GetStructByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructBytePropertyImplementation))
			.Function("SetStructByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructBytePropertyImplementation))
			.Function("GetStructUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructUInt16PropertyImplementation))
			.Function("SetStructUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructUInt16PropertyImplementation))
			.Function("GetStructUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructUInt32PropertyImplementation))
			.Function("SetStructUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructUInt32PropertyImplementation))
			.Function("GetStructUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructUInt64PropertyImplementation))
			.Function("SetStructUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructUInt64PropertyImplementation))
			.Function("GetStructInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructInt8PropertyImplementation))
			.Function("SetStructInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructInt8PropertyImplementation))
			.Function("GetStructInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructInt16PropertyImplementation))
			.Function("SetStructInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructInt16PropertyImplementation))
			.Function("GetStructIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructIntPropertyImplementation))
			.Function("SetStructIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructIntPropertyImplementation))
			.Function("GetStructInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructInt64PropertyImplementation))
			.Function("SetStructInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructInt64PropertyImplementation))
			.Function("GetStructBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructBoolPropertyImplementation))
			.Function("SetStructBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructBoolPropertyImplementation))
			.Function("GetStructFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructFloatPropertyImplementation))
			.Function("SetStructFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructFloatPropertyImplementation))
			.Function("GetStructObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructObjectPropertyImplementation))
			.Function("SetStructObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructObjectPropertyImplementation))
			.Function("GetStructClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructClassPropertyImplementation))
			.Function("SetStructClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructClassPropertyImplementation))
			.Function("GetStructInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructInterfacePropertyImplementation))
			.Function("SetStructInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructInterfacePropertyImplementation))
			.Function("GetStructArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructArrayPropertyImplementation))
			.Function("SetStructArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructArrayPropertyImplementation))
			.Function("GetStructWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructWeakObjectPropertyImplementation))
			.Function("SetStructWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructWeakObjectPropertyImplementation))
			.Function("GetStructLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructLazyObjectPropertyImplementation))
			.Function("SetStructLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructLazyObjectPropertyImplementation))
			.Function("GetStructSoftClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructSoftClassPropertyImplementation))
			.Function("SetStructSoftClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructSoftClassPropertyImplementation))
			.Function("GetStructSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructSoftObjectPropertyImplementation))
			.Function("SetStructSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructSoftObjectPropertyImplementation))
			.Function("GetStructDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructDoublePropertyImplementation))
			.Function("SetStructDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructDoublePropertyImplementation))
			.Function("GetStructMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructMapPropertyImplementation))
			.Function("SetStructMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructMapPropertyImplementation))
			.Function("GetStructSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructSetPropertyImplementation))
			.Function("SetStructSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructSetPropertyImplementation))
			.Function("GetStructFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetStructFieldPathPropertyImplementation))
			.Function("SetStructFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetStructFieldPathPropertyImplementation))
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
