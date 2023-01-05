#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"

struct FRegisterProperty
{
	FRegisterProperty()
	{
		FBindingClassBuilder(TEXT("Property"), NAMESPACE_PROPERTY)
			.Function("GetByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetBytePropertyImplementation))
			.Function("SetByteProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetBytePropertyImplementation))
			.Function("GetUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetUInt16PropertyImplementation))
			.Function("SetUInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetUInt16PropertyImplementation))
			.Function("GetUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetUInt32PropertyImplementation))
			.Function("SetUInt32Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetUInt32PropertyImplementation))
			.Function("GetUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetUInt64PropertyImplementation))
			.Function("SetUInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetUInt64PropertyImplementation))
			.Function("GetInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetInt8PropertyImplementation))
			.Function("SetInt8Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetInt8PropertyImplementation))
			.Function("GetInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetInt16PropertyImplementation))
			.Function("SetInt16Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetInt16PropertyImplementation))
			.Function("GetIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetIntPropertyImplementation))
			.Function("SetIntProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetIntPropertyImplementation))
			.Function("GetInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_GetInt64PropertyImplementation))
			.Function("SetInt64Property",
			          static_cast<void*>(FPropertyImplementation::Property_SetInt64PropertyImplementation))
			.Function("GetBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetBoolPropertyImplementation))
			.Function("SetBoolProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetBoolPropertyImplementation))
			.Function("GetFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetFloatPropertyImplementation))
			.Function("SetFloatProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetFloatPropertyImplementation))
			.Function("GetObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetObjectPropertyImplementation))
			.Function("SetObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetObjectPropertyImplementation))
			.Function("GetClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetClassPropertyImplementation))
			.Function("SetClassProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetClassPropertyImplementation))
			.Function("GetInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetInterfacePropertyImplementation))
			.Function("SetInterfaceProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetInterfacePropertyImplementation))
			.Function("GetArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetArrayPropertyImplementation))
			.Function("SetArrayProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetArrayPropertyImplementation))
			.Function("GetWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetWeakObjectPropertyImplementation))
			.Function("SetWeakObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetWeakObjectPropertyImplementation))
			.Function("GetLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetLazyObjectPropertyImplementation))
			.Function("SetLazyObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetLazyObjectPropertyImplementation))
			.Function("GetSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetSoftObjectPropertyImplementation))
			.Function("SetSoftObjectProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetSoftObjectPropertyImplementation))
			.Function("GetDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetDoublePropertyImplementation))
			.Function("SetDoubleProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetDoublePropertyImplementation))
			.Function("GetMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetMapPropertyImplementation))
			.Function("SetMapProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetMapPropertyImplementation))
			.Function("GetSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetSetPropertyImplementation))
			.Function("SetSetProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetSetPropertyImplementation))
			.Function("GetFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_GetFieldPathPropertyImplementation))
			.Function("SetFieldPathProperty",
			          static_cast<void*>(FPropertyImplementation::Property_SetFieldPathPropertyImplementation))
			.Register();
	}
};

static FRegisterProperty RegisterProperty;

PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Int8, int8)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Int, int32)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Bool, bool)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Float, float)

COMPOUND_PROPERTY_IMPLEMENTATION(Object, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(Class, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(Interface, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(Array, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(WeakObject, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(LazyObject, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(SoftObject, MonoObject)

PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

COMPOUND_PROPERTY_IMPLEMENTATION(Map, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(Set, MonoObject)

COMPOUND_PROPERTY_IMPLEMENTATION(FieldPath, MonoObject)
