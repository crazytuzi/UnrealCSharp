#pragma once

#include "Macro.h"

#define CPT_ENUM CPT_Unused_Index_21

#define CPT_ARRAY CPT_Unused_Index_22

#define GET_PROPERTY_TYPE(FPropertyType, EPropertyType) if (CastField<FPropertyType>(Property)) return EPropertyType;

#define NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyDescriptorType) if (CastField<FPropertyType>(InProperty)) return new FPropertyDescriptorType(InProperty);

#define NEW_PROPERTY_DESCRIPTOR(FPropertyType) NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyType##Descriptor)

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) static void Get##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, Type& OutValue);

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) static void Set##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, Type InValue);

#define PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	GET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
void FPropertyImplementation::Get##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, Type& OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get(); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), &OutValue); \
		} \
	} \
}

#define SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
void FPropertyImplementation::Set##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, Type InValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get(); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Set(&InValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress)); \
		} \
	} \
}

#define PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	GET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) static void Get##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, MonoObject** OutValue);

#define SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	GET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	SET_COMPOUND_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
void FPropertyImplementation::Get##PropertyType##PropertyImplementation(const MonoObject* InMonoObject, const UTF16CHAR* InPropertyName, MonoObject** OutValue) \
{ \
	UStruct* InStruct = nullptr; \
	if (const auto FoundAddress = FCSharpEnvironment::GetEnvironment()->GetAddress(InMonoObject, InStruct)) \
	{ \
		const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get(); \
		if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor( \
			InStruct, PropertyName)) \
		{ \
			PropertyDescriptor->Get(PropertyDescriptor->ContainerPtrToValuePtr<void>(FoundAddress), OutValue); \
		} \
	} \
}

#define SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) SET_PRIMITIVE_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	GET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	SET_COMPOUND_PROPERTY_IMPLEMENTATION(PropertyType, Type)

#define REGISTER_GET_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Type) \
	FMonoInternalCall::RegisterInternalCall( \
		TCHAR_TO_ANSI(*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_PROPERTY), CLASS_PROPERTY_IMPLEMENTATION) + FString("::Get")+ STRING(Type) + FString("PropertyImplementation"))), \
		static_cast<void*>(FPropertyImplementation::Get##Type##PropertyImplementation));

#define REGISTER_SET_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Type) \
	FMonoInternalCall::RegisterInternalCall( \
		TCHAR_TO_ANSI(*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_PROPERTY), CLASS_PROPERTY_IMPLEMENTATION) + FString("::Set")+ STRING(Type) + FString("PropertyImplementation"))), \
		static_cast<void*>(FPropertyImplementation::Set##Type##PropertyImplementation));

#define REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Type) \
	REGISTER_GET_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Type) \
	REGISTER_SET_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Type)
