#pragma once

#include "Macro/PropertyMacro.h"
#include "mono/metadata/object.h"

class FPropertyImplementation
{
public:
	PROPERTY_IMPLEMENTATION_DEFINE(Byte, uint8)

	PROPERTY_IMPLEMENTATION_DEFINE(UInt16, uint16)

	PROPERTY_IMPLEMENTATION_DEFINE(UInt32, uint32)

	PROPERTY_IMPLEMENTATION_DEFINE(Int8, int8)

	PROPERTY_IMPLEMENTATION_DEFINE(Int16, int16)

	PROPERTY_IMPLEMENTATION_DEFINE(Int, int32)

	PROPERTY_IMPLEMENTATION_DEFINE(Int64, int64)

	PROPERTY_IMPLEMENTATION_DEFINE(Bool, bool)

	PROPERTY_IMPLEMENTATION_DEFINE(Float, float)

	static void GetObjectPropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName,
	                                            MonoObject** OutValue);

	SET_PROPERTY_IMPLEMENTATION_DEFINE(Object, MonoObject)

	// @TODO

	PROPERTY_IMPLEMENTATION_DEFINE(Array, MonoArray)

	// @TODO

	PROPERTY_IMPLEMENTATION_DEFINE(Double, double)

	// @TODO
};
