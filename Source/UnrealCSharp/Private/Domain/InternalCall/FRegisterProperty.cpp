#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/PropertyMacro.h"

struct FRegisterProperty
{
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

	FRegisterProperty()
	{
		FClassBuilder(TEXT("Property"), NAMESPACE_LIBRARY)
			.Function("GetObjectByteProperty", GetObjectBytePropertyImplementation)
			.Function("SetObjectByteProperty", SetObjectBytePropertyImplementation)
			.Function("GetObjectUInt16Property", GetObjectUInt16PropertyImplementation)
			.Function("SetObjectUInt16Property", SetObjectUInt16PropertyImplementation)
			.Function("GetObjectUInt32Property", GetObjectUInt32PropertyImplementation)
			.Function("SetObjectUInt32Property", SetObjectUInt32PropertyImplementation)
			.Function("GetObjectUInt64Property", GetObjectUInt64PropertyImplementation)
			.Function("SetObjectUInt64Property", SetObjectUInt64PropertyImplementation)
			.Function("GetObjectSByteProperty", GetObjectSBytePropertyImplementation)
			.Function("SetObjectSByteProperty", SetObjectSBytePropertyImplementation)
			.Function("GetObjectInt16Property", GetObjectInt16PropertyImplementation)
			.Function("SetObjectInt16Property", SetObjectInt16PropertyImplementation)
			.Function("GetObjectIntProperty", GetObjectIntPropertyImplementation)
			.Function("SetObjectIntProperty", SetObjectIntPropertyImplementation)
			.Function("GetObjectInt64Property", GetObjectInt64PropertyImplementation)
			.Function("SetObjectInt64Property", SetObjectInt64PropertyImplementation)
			.Function("GetObjectBoolProperty", GetObjectBoolPropertyImplementation)
			.Function("SetObjectBoolProperty", SetObjectBoolPropertyImplementation)
			.Function("GetObjectFloatProperty", GetObjectFloatPropertyImplementation)
			.Function("SetObjectFloatProperty", SetObjectFloatPropertyImplementation)
			.Function("GetObjectCompoundProperty", GetObjectCompoundPropertyImplementation)
			.Function("SetObjectCompoundProperty", SetObjectCompoundPropertyImplementation)
			.Function("GetObjectDoubleProperty", GetObjectDoublePropertyImplementation)
			.Function("SetObjectDoubleProperty", SetObjectDoublePropertyImplementation)
			.Function("GetStructByteProperty", GetStructBytePropertyImplementation)
			.Function("SetStructByteProperty", SetStructBytePropertyImplementation)
			.Function("GetStructUInt16Property", GetStructUInt16PropertyImplementation)
			.Function("SetStructUInt16Property", SetStructUInt16PropertyImplementation)
			.Function("GetStructUInt32Property", GetStructUInt32PropertyImplementation)
			.Function("SetStructUInt32Property", SetStructUInt32PropertyImplementation)
			.Function("GetStructUInt64Property", GetStructUInt64PropertyImplementation)
			.Function("SetStructUInt64Property", SetStructUInt64PropertyImplementation)
			.Function("GetStructSByteProperty", GetStructSBytePropertyImplementation)
			.Function("SetStructSByteProperty", SetStructSBytePropertyImplementation)
			.Function("GetStructInt16Property", GetStructInt16PropertyImplementation)
			.Function("SetStructInt16Property", SetStructInt16PropertyImplementation)
			.Function("GetStructIntProperty", GetStructIntPropertyImplementation)
			.Function("SetStructIntProperty", SetStructIntPropertyImplementation)
			.Function("GetStructInt64Property", GetStructInt64PropertyImplementation)
			.Function("SetStructInt64Property", SetStructInt64PropertyImplementation)
			.Function("GetStructBoolProperty", GetStructBoolPropertyImplementation)
			.Function("SetStructBoolProperty", SetStructBoolPropertyImplementation)
			.Function("GetStructFloatProperty", GetStructFloatPropertyImplementation)
			.Function("SetStructFloatProperty", SetStructFloatPropertyImplementation)
			.Function("GetStructCompoundProperty", GetStructCompoundPropertyImplementation)
			.Function("SetStructCompoundProperty", SetStructCompoundPropertyImplementation)
			.Function("GetStructDoubleProperty", GetStructDoublePropertyImplementation)
			.Function("SetStructDoubleProperty", SetStructDoublePropertyImplementation)
			.Register();
	}
};

static FRegisterProperty RegisterProperty;
