#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/PropertyMacro.h"

namespace
{
	struct FRegisterProperty
	{
		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(SByte, int8)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int32, int32)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Boolean, bool)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Single, float)

		OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(Compound)

		OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Byte, uint8)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt16, uint16)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt32, uint32)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(UInt64, uint64)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(SByte, int8)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int16, int16)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int32, int32)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Int64, int64)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Boolean, bool)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Single, float)

		STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(Compound)

		STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(Double, double)

		FRegisterProperty()
		{
			FClassBuilder(TEXT("FProperty"), NAMESPACE_LIBRARY, true)
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
				.Function("GetObjectInt32Property", GetObjectInt32PropertyImplementation)
				.Function("SetObjectInt32Property", SetObjectInt32PropertyImplementation)
				.Function("GetObjectInt64Property", GetObjectInt64PropertyImplementation)
				.Function("SetObjectInt64Property", SetObjectInt64PropertyImplementation)
				.Function("GetObjectBooleanProperty", GetObjectBooleanPropertyImplementation)
				.Function("SetObjectBooleanProperty", SetObjectBooleanPropertyImplementation)
				.Function("GetObjectSingleProperty", GetObjectSinglePropertyImplementation)
				.Function("SetObjectSingleProperty", SetObjectSinglePropertyImplementation)
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
				.Function("GetStructInt32Property", GetStructInt32PropertyImplementation)
				.Function("SetStructInt32Property", SetStructInt32PropertyImplementation)
				.Function("GetStructInt64Property", GetStructInt64PropertyImplementation)
				.Function("SetStructInt64Property", SetStructInt64PropertyImplementation)
				.Function("GetStructBooleanProperty", GetStructBooleanPropertyImplementation)
				.Function("SetStructBooleanProperty", SetStructBooleanPropertyImplementation)
				.Function("GetStructSingleProperty", GetStructSinglePropertyImplementation)
				.Function("SetStructSingleProperty", SetStructSinglePropertyImplementation)
				.Function("GetStructCompoundProperty", GetStructCompoundPropertyImplementation)
				.Function("SetStructCompoundProperty", SetStructCompoundPropertyImplementation)
				.Function("GetStructDoubleProperty", GetStructDoublePropertyImplementation)
				.Function("SetStructDoubleProperty", SetStructDoublePropertyImplementation);
		}
	};

	FRegisterProperty RegisterProperty;
}
