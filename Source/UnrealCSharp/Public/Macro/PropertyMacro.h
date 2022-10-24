#pragma once

#include "Macro.h"

#define GET_PROPERTY_TYPE(FPropertyType, EPropertyType) if (CastField<FPropertyType>(Property)) return EPropertyType;

#define NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyDescriptorType) if (CastField<FPropertyType>(InProperty)) return new FPropertyDescriptorType(InProperty);

#define NEW_PROPERTY_DESCRIPTOR(FPropertyType) NEW_PROPERTY_DESCRIPTOR_IMPLEMENTATION(FPropertyType, FPropertyType##Descriptor)

#define GET_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) static void Get##PropertyType##PropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName, Type& OutValue);

#define SET_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) static void Set##PropertyType##PropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName, Type InValue);

#define PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	GET_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type) \
	SET_PROPERTY_IMPLEMENTATION_DEFINE(PropertyType, Type)

#define GET_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
void FPropertyImplementation::Get##PropertyType##PropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName, Type& OutValue) \
{ \
	if (const auto InObject = FCSharpEnvironment::GetEnvironment()->GetObject(&InMonoObject)) \
	{ \
		if (const auto InClass = InObject->GetClass()) \
		{ \
			const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get(); \
\
			if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor(InClass, PropertyName)) \
			{ \
				PropertyDescriptor->Get(InObject, &OutValue); \
			} \
		} \
	} \
}

#define SET_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
void FPropertyImplementation::Set##PropertyType##PropertyImplementation(MonoObject InMonoObject, const UTF16CHAR* InPropertyName, Type InValue) \
{ \
	if (const auto InObject = FCSharpEnvironment::GetEnvironment()->GetObject(&InMonoObject)) \
	{ \
		if (const auto InClass = InObject->GetClass()) \
		{ \
			const auto PropertyName = StringCast<TCHAR>(InPropertyName + 10).Get(); \
\
			if (const auto PropertyDescriptor = FCSharpEnvironment::GetEnvironment()->GetPropertyDescriptor(InClass, PropertyName)) \
			{ \
				PropertyDescriptor->Set(&InValue, InObject); \
			} \
		} \
	} \
}

#define PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	GET_PROPERTY_IMPLEMENTATION(PropertyType, Type) \
	SET_PROPERTY_IMPLEMENTATION(PropertyType, Type)

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
