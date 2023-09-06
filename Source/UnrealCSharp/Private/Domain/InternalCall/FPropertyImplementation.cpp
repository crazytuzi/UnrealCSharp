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
			.Function("GetObjectSByteProperty", FPropertyImplementation::Property_GetObjectSBytePropertyImplementation)
			.Function("SetObjectSByteProperty", FPropertyImplementation::Property_SetObjectSBytePropertyImplementation)
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
			.Function("GetObjectCompoundProperty",
			          FPropertyImplementation::Property_GetObjectCompoundPropertyImplementation)
			.Function("SetObjectCompoundProperty",
			          FPropertyImplementation::Property_SetObjectCompoundPropertyImplementation)
			.Function("GetObjectDoubleProperty",
			          FPropertyImplementation::Property_GetObjectDoublePropertyImplementation)
			.Function("SetObjectDoubleProperty",
			          FPropertyImplementation::Property_SetObjectDoublePropertyImplementation)
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
			.Function("GetStructSByteProperty", FPropertyImplementation::Property_GetStructSBytePropertyImplementation)
			.Function("SetStructSByteProperty", FPropertyImplementation::Property_SetStructSBytePropertyImplementation)
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
			.Function("GetStructCompoundProperty",
			          FPropertyImplementation::Property_GetStructCompoundPropertyImplementation)
			.Function("SetStructCompoundProperty",
			          FPropertyImplementation::Property_SetStructCompoundPropertyImplementation)
			.Function("GetStructDoubleProperty",
			          FPropertyImplementation::Property_GetStructDoublePropertyImplementation)
			.Function("SetStructDoubleProperty",
			          FPropertyImplementation::Property_SetStructDoublePropertyImplementation)
			.Register();
	}
};

static FRegisterProperty RegisterProperty;

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(SByte, int8)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int, int32)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Bool, bool)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Float, float)

OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Compound)

OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(SByte, int8)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int, int32)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Bool, bool)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Float, float)

STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Compound)

STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)
