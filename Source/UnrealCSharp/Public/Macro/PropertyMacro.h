#pragma once

#define GET_PROPERTY_TYPE(FPropertyType, EPropertyType) if (CastField<FPropertyType>(Property)) return EPropertyType;

#define NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyDescriptorType) if (CastField<FPropertyType>(InProperty)) return new FPropertyDescriptorType(InProperty);

#define NEW_PROPERTY_DESCRIPTOR(FPropertyType) NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyType##Descriptor)

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType, Type) static void Property_Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, Type& OutValue);

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType, Type) static void Property_Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, Type InValue);

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
void FPropertyImplementation::Property_Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, Type& OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType>(InGarbageCollectionHandle, InStruct)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetPropertyDescriptor( \
			InStruct, InPropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), &OutValue); \
		} \
	} \
}

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
void FPropertyImplementation::Property_Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, Type InValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType>(InGarbageCollectionHandle, InStruct)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetPropertyDescriptor( \
			InStruct, InPropertyName)) \
		{ \
			PropertyDescriptor->Set(&InValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType) \
void FPropertyImplementation::Property_Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, MonoObject** OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType>(InGarbageCollectionHandle, InStruct)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetPropertyDescriptor( \
			InStruct, InPropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), OutValue); \
		} \
	} \
}

#define SET_COMPOUND_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType) \
void FPropertyImplementation::Property_Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, MonoObject* InValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType>(InGarbageCollectionHandle, InStruct)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetPropertyDescriptor( \
			InStruct, InPropertyName)) \
		{ \
			PropertyDescriptor->Set(InValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType) static void Property_Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, MonoObject** OutValue);

#define SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(StructType, PropertyType) static void Property_Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InPropertyName, MonoObject* InValue);

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

#define OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Object, PropertyType)

#define OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Object, PropertyType)

#define OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) \
	OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) \
	OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType)

#define OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType)

#define OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType)

#define OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType)

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

#define STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Struct, PropertyType)

#define STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(Struct, PropertyType)

#define STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) \
	STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType) \
	STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType)

#define STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType)

#define STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType)

#define STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType)
