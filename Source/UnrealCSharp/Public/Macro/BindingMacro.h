#pragma once

#define BINDING_STR(Str) #Str

#define BINDING_REMOVE_PREFIX_CLASS(Class) FString(TEXT(BINDING_STR(Class))).RightChop(1)

#define BINDING_CLASS(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_PREFIX_CLASS(Class); } \
};

#define BINDING_CLASS_IMPLEMENTATION(A) FString::Printf(TEXT("%sImplementation"), *A)

#define BINDING_COMBINE_FUNCTION(A, B) FString::Printf(TEXT("%s_%sImplementation"), *A, *B)

#define BINDING_PROPERTY_SET FString(TEXT("Set"))

#define BINDING_PROPERTY_GET FString(TEXT("Get"))

#define BINDING_PROPERTY_BUILDER_SET(Property) TPropertyBuilder<decltype(Property), Property>::Set

#define BINDING_PROPERTY_BUILDER_GET(Property) TPropertyBuilder<decltype(Property), Property>::Get

#define BINDING_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), BINDING_PROPERTY_BUILDER_SET(Property)

#define BINDING_READONLY_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), nullptr
