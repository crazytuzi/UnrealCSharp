#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Environment/FCSharpEnvironment.h"

PROPERTY_IMPLEMENTATION(Byte, uint8)

PROPERTY_IMPLEMENTATION(UInt16, uint16)

PROPERTY_IMPLEMENTATION(UInt32, uint32)

PROPERTY_IMPLEMENTATION(Int8, int8)

PROPERTY_IMPLEMENTATION(Int16, int16)

PROPERTY_IMPLEMENTATION(Int, int32)

PROPERTY_IMPLEMENTATION(Int64, int64)

PROPERTY_IMPLEMENTATION(Bool, bool)

PROPERTY_IMPLEMENTATION(Float, float)

void FPropertyImplementation::GetObjectPropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName,
                                                              MonoObject** OutValue)
{
	UStruct* InStruct = nullptr;

	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress(&InMonoObject, InStruct))
	{
		const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get();

		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor(
			InStruct, PropertyName))
		{
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), OutValue);
		}
	}
}

SET_PROPERTY_IMPLEMENTATION(Object, MonoObject)

// @TODO

// PROPERTY_IMPLEMENTATION(Array, MonoArray)

// @TODO

PROPERTY_IMPLEMENTATION(Double, double)

// @TODO
