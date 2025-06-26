#pragma once

#include "Template/TAccessPrivate.inl"
#include "Template/TAccessPrivateStub.inl"

#define ACCESS_PRIVATE_MEMBER_PROPERTY(Class, PropertyName, PropertyType) \
struct Class##_##PropertyName \
{ \
	typedef PropertyType (Class::*Type); \
}; \
template struct TAccessPrivateStub<Class##_##PropertyName, &Class::PropertyName>;

#define ACCESS_PRIVATE_STATIC_PROPERTY(Class, PropertyName, PropertyType) \
struct Class##_##PropertyName \
{ \
	typedef PropertyType (*Type); \
}; \
template struct TAccessPrivateStub<Class##_##PropertyName, &Class::PropertyName>;

#define ACCESS_PRIVATE_MEMBER_FUNCTION(Class, FunctionName, ReturnType, ...) \
struct Class##_##FunctionName \
{ \
	typedef ReturnType (Class::*Type)(__VA_ARGS__); \
}; \
template struct TAccessPrivateStub<Class##_##FunctionName, &Class::FunctionName>;

#define ACCESS_PRIVATE_CONST_MEMBER_FUNCTION(Class, FunctionName, ReturnType, ...) \
struct Class##_##FunctionName \
{ \
	typedef ReturnType (Class::*Type)(__VA_ARGS__) const; \
}; \
template struct TAccessPrivateStub<Class##_##FunctionName, &Class::FunctionName>;

#define ACCESS_PRIVATE_STATIC_FUNCTION(Class, FunctionName, ReturnType, ...) \
struct Class##_##FunctionName \
{ \
	typedef ReturnType (*Type)(__VA_ARGS__); \
}; \
template struct TAccessPrivateStub<Class##_##FunctionName, &Class::FunctionName>;
