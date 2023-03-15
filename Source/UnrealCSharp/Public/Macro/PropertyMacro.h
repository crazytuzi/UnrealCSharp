#pragma once

#define CPT_CLASS_REFERENCE CPT_Unused_Index_19

#define CPT_ENUM CPT_Unused_Index_21

#define CPT_ARRAY CPT_Unused_Index_22

#define GET_PROPERTY_TYPE(FPropertyType, EPropertyType) if (CastField<FPropertyType>(Property)) return EPropertyType;

#define NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyDescriptorType) if (CastField<FPropertyType>(InProperty)) return new FPropertyDescriptorType(InProperty);

#define NEW_PROPERTY_DESCRIPTOR(FPropertyType) NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyType##Descriptor)

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType, Type) static void Property_Get##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, Type& OutValue);

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType, Type) static void Property_Set##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, Type InValue);

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
void FPropertyImplementation::Property_Get##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, Type& OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress<##TemplateType##>(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = FName( \
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InPropertyName)); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), &OutValue); \
		} \
	} \
}

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
void FPropertyImplementation::Property_Set##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, Type InValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress<##TemplateType##>(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = FName( \
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InPropertyName)); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Set(&InValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
void FPropertyImplementation::Property_Get##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, MonoObject** OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress<##TemplateType##>(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = FName( \
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InPropertyName)); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), OutValue); \
		} \
	} \
}

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType, Type) static void Property_Get##StructType##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, MonoString* InPropertyName, MonoObject** OutValue);

#define OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(Object, PropertyType, Type)

#define OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(Object, PropertyType, Type)

#define OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType, Type)

#define OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType, Type)

#define OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Object, PropertyType, Type)

#define OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType, Type)

#define OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(Struct, PropertyType, Type)

#define STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(Struct, PropertyType, Type)

#define STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType, Type)

#define STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType, Type)

#define STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Struct, PropertyType, Type)

#define STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType, Type)

#define STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type)
