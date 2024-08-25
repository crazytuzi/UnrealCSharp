#pragma once

#define GET_PROPERTY_TYPE(FPropertyType, EPropertyType) if (CastField<FPropertyType>(Property)) return EPropertyType;

#define NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyDescriptorType) if (auto Property = CastField<FPropertyType>(InProperty)) return new FPropertyDescriptorType(Property);

#define NEW_PROPERTY_DESCRIPTOR(FPropertyType) NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyType##Descriptor)

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
static Type Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InPropertyHash) \
{ \
	Type Value{}; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType, void*>(InGarbageCollectionHandle)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddPropertyDescriptor(InPropertyHash)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), &Value); \
		} \
	} \
	return Value; \
}

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType, Type) \
static void Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InPropertyHash, const Type InValue) \
{ \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType, void*>(InGarbageCollectionHandle)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddPropertyDescriptor(InPropertyHash)) \
		{ \
			PropertyDescriptor->Set(const_cast<Type*>(&InValue), PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType) \
static MonoObject* Get##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InPropertyHash) \
{ \
	MonoObject* Value{}; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType, void*>(InGarbageCollectionHandle)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddPropertyDescriptor(InPropertyHash)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), &Value); \
		} \
	} \
	return Value; \
}

#define SET_COMPOUND_PROPERTY_IMPLEMENTATION(StructType, TemplateType, PropertyType) \
static void Set##StructType##PropertyType##PropertyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InPropertyHash, const FGarbageCollectionHandle InValue) \
{ \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment().GetAddress<TemplateType, void*>(InGarbageCollectionHandle)) \
	{ \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddPropertyDescriptor(InPropertyHash)) \
		{ \
			PropertyDescriptor->Set(const_cast<FGarbageCollectionHandle*>(&InValue), PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType, Type)

#define OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType, Type)

#define OBJECT_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	OBJECT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType)

#define OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION(Object, UObject, PropertyType)

#define OBJECT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	OBJECT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	OBJECT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType)

#define STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType, Type)

#define STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType, Type)

#define STRUCT_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	STRUCT_SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) GET_COMPOUND_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType)

#define STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) SET_COMPOUND_PROPERTY_IMPLEMENTATION(Struct, UScriptStruct, PropertyType)

#define STRUCT_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	STRUCT_GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType) \
	STRUCT_SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType)
