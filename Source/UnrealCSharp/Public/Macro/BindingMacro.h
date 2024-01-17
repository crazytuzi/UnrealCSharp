﻿#pragma once

#include "CoreMacro/BindingMacro.h"
#include "Binding/Function/TFunctionPointer.inl"
#include "Binding/Function/TFunctionBuilder.inl"
#include "Binding/Function/TConstructorBuilder.inl"
#include "Binding/Function/TDestructorBuilder.inl"
#include "Binding/Function/TSubscriptBuilder.inl"
#include "Binding/Template/TClassName.inl"
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Binding/Core/TPropertyValue.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "Binding/Function/TArgument.inl"
#include "Binding/Function/TReturnValue.inl"
#include "Binding/Function/TOverloadBuilder.inl"
#include "Template/TIsScriptStruct.inl"
#include "Template/TIsNotUEnum.inl"

#define BINDING_STR(Str) #Str

#define BINDING_REMOVE_NAMESPACE_CLASS_STR(Class) FString(TEXT(BINDING_STR(Class))).RightChop( \
	FString(TEXT(BINDING_STR(Class))).Find(TEXT(":"), ESearchCase::IgnoreCase, ESearchDir::FromEnd) + 1)

#define BINDING_REMOVE_PREFIX_CLASS_STR(Class) BINDING_REMOVE_NAMESPACE_CLASS_STR(Class).RightChop(1)

#define BINDING_REFLECTION_CLASS(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
};

#define BINDING_CLASS(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
}; \
template <typename T> \
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> \
{ \
	static FString Get() \
	{ \
		return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); \
	} \
}; \
template <typename T> \
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TBindingPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TBindingPropertyValue<T, T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<Result>>, Class>>> : \
	TBindingPropertyBuilder<InClass, Result, Member> \
{ \
}; \
template <typename Result, Result* Member> \
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<Result>>, Class>>> : \
	TBindingPropertyBuilder<void, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TBindingArgument<T> \
{ \
	using TBindingArgument<T>::TBindingArgument; \
}; \
template <typename T> \
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<T>>, Class>>> : \
	TBindingReturnValue<T> \
{ \
	using TBindingReturnValue<T>::TBindingReturnValue; \
};

#define BINDING_PROJECT_CLASS(Class) \
BINDING_CLASS(Class) \
template <typename T> \
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> \
{ \
	static TArray<FString> Get() \
	{ \
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, FString(FApp::GetProjectName()))}; \
	} \
};

#define BINDING_ENGINE_CLASS(Class) \
BINDING_CLASS(Class) \
template <typename T> \
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> \
{ \
	static TArray<FString> Get() \
	{ \
		return {static_cast<FName>(GLongCoreUObjectPackageName).ToString().RightChop(1).Replace(TEXT("/"), TEXT("."))}; \
	} \
};

#define BINDING_SCRIPT_STRUCT(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
}; \
template <typename T> \
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
}; \
template <typename T> \
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> \
{ \
	static TArray<FString> Get() \
	{ \
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(TBaseStructure<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>>::Get())}; \
	} \
}; \
template <typename T> \
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TScriptStructPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TScriptStructPropertyValue<T, T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, Class>>> : \
	TScriptStructPropertyBuilder<InClass, Result, Member> \
{ \
}; \
template <typename Result, Result* Member> \
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, Class>>> : \
	TScriptStructPropertyBuilder<void, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<std::remove_reference_t<T>>>, Class>, T>> : \
	TScriptStructArgument<T> \
{ \
	using TScriptStructArgument<T>::TScriptStructArgument; \
}; \
template <typename T> \
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_pointer_t<T>>, Class>>> : \
	TScriptStructReturnValue<T> \
{ \
	using TScriptStructReturnValue<T>::TScriptStructReturnValue; \
}; \
template <> \
struct TIsScriptStruct<Class> \
{ \
	enum { Value = true }; \
};

#define BINDING_ENUM(Class) \
template <> \
struct TClassName<Class> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
}; \
template <typename T> \
struct TName<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> \
{ \
	static FString Get() { return BINDING_REMOVE_NAMESPACE_CLASS_STR(Class); } \
}; \
template <typename T> \
struct TPropertyClass<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> : \
	TBindingEnumPropertyClass<T> \
{ \
}; \
template <typename T> \
struct TPropertyValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> : \
	TBindingEnumPropertyValue<T> \
{ \
}; \
template <typename InClass, typename Result, Result InClass::* Member> \
struct TPropertyBuilder<Result InClass::*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, Class>>> : \
	TBindingEnumPropertyBuilder<InClass, Result, Member> \
{ \
}; \
template <typename Result, Result* Member> \
struct TPropertyBuilder<Result*, Member, std::enable_if_t<std::is_same_v<std::decay_t<Result>, Class>>> : \
	TBindingEnumPropertyBuilder<void, Result, Member> \
{ \
}; \
template <typename T> \
struct TArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> : \
	TBindingEnumArgument<T> \
{ \
	using TBindingEnumArgument<T>::TBindingEnumArgument; \
}; \
template <typename T> \
struct TReturnValue<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>>> : \
	TBindingEnumReturnValue<T> \
{ \
	using TBindingEnumReturnValue<T>::TBindingEnumReturnValue; \
}; \
template <> \
struct TIsNotUEnum<Class> \
{ \
	enum { Value = true }; \
};

#define BINDING_PROJECT_ENUM(Class) \
BINDING_ENUM(Class) \
template <typename T> \
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> \
{ \
	static TArray<FString> Get() \
	{ \
		return {COMBINE_NAMESPACE(NAMESPACE_ROOT, FString(FApp::GetProjectName()))}; \
	} \
};

#define BINDING_ENGINE_ENUM(Class) \
BINDING_ENUM(Class) \
template <typename T> \
struct TNameSpace<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, Class>, T>> \
{ \
	static TArray<FString> Get() \
	{ \
		return {static_cast<FName>(GLongCoreUObjectPackageName).ToString().RightChop(1).Replace(TEXT("/"), TEXT("."))}; \
	} \
};

#define BINDING_PROPERTY_BUILDER_SET(Property) TPropertyBuilder<decltype(Property), Property>::Set

#define BINDING_PROPERTY_BUILDER_GET(Property) TPropertyBuilder<decltype(Property), Property>::Get

#define BINDING_PROPERTY_BUILDER_INFO(Property) TPropertyBuilder<decltype(Property), Property>::Info()

#if WITH_PROPERTY_INFO
#define BINDING_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), BINDING_PROPERTY_BUILDER_SET(Property), BINDING_PROPERTY_BUILDER_INFO(Property)
#else
#define BINDING_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), BINDING_PROPERTY_BUILDER_SET(Property)
#endif

#if WITH_PROPERTY_INFO
#define BINDING_READONLY_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), nullptr, BINDING_PROPERTY_BUILDER_INFO(Property)
#else
#define BINDING_READONLY_PROPERTY(Property) BINDING_PROPERTY_BUILDER_GET(Property), nullptr
#endif

#define BINDING_FUNCTION_BUILDER_INVOKE(Function) TFunctionPointer<decltype(&TFunctionBuilder<decltype(Function), Function>::Invoke)>(&TFunctionBuilder<decltype(Function), Function>::Invoke).Value.Pointer

#define BINDING_FUNCTION_BUILDER_INFO(Function) TFunctionBuilder<decltype(Function), Function>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_FUNCTION(Function) BINDING_FUNCTION_BUILDER_INVOKE(Function), BINDING_FUNCTION_BUILDER_INFO(Function)
#else
#define BINDING_FUNCTION(Function) BINDING_FUNCTION_BUILDER_INVOKE(Function)
#endif

#define BINDING_OVERLOAD_BUILDER_INVOKE(Signature, Function) TFunctionPointer<decltype(&TFunctionBuilder<Signature, Function>::Invoke)>(&TFunctionBuilder<Signature, Function>::Invoke).Value.Pointer

#define BINDING_OVERLOAD_BUILDER_INFO(Signature, Function) TFunctionBuilder<Signature, Function>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_OVERLOAD(Signature, Function) BINDING_OVERLOAD_BUILDER_INVOKE(Signature, Function), BINDING_OVERLOAD_BUILDER_INFO(Signature, Function)
#else
#define BINDING_OVERLOAD(Signature, Function) BINDING_OVERLOAD_BUILDER_INVOKE(Signature, Function)
#endif

#if WITH_FUNCTION_INFO
#define BINDING_OVERLOADS(...) TOverloadBuilder<void*, FFunctionInfo*>::Get(##__VA_ARGS__)
#else
#define BINDING_OVERLOADS(...) TOverloadBuilder<void*>::Get(##__VA_ARGS__)
#endif

#define BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ...) TFunctionPointer<decltype(&TConstructorBuilder<T, ##__VA_ARGS__>::Invoke)>(&TConstructorBuilder<T, ##__VA_ARGS__>::Invoke).Value.Pointer

#define BINDING_CONSTRUCTOR_BUILDER_INFO(T, ...) TConstructorBuilder<T, ##__VA_ARGS__>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_CONSTRUCTOR(T, ...) BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ##__VA_ARGS__), BINDING_CONSTRUCTOR_BUILDER_INFO(T, ##__VA_ARGS__)
#else
#define BINDING_CONSTRUCTOR(T, ...) BINDING_CONSTRUCTOR_BUILDER_INVOKE(T, ##__VA_ARGS__)
#endif

#define BINDING_DESTRUCTOR_BUILDER_INVOKE(...) TFunctionPointer<decltype(&TDestructorBuilder<##__VA_ARGS__>::Invoke)>(&TDestructorBuilder<##__VA_ARGS__>::Invoke).Value.Pointer

#define BINDING_DESTRUCTOR_BUILDER_INFO(...) TDestructorBuilder<##__VA_ARGS__>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_DESTRUCTOR(...) BINDING_DESTRUCTOR_BUILDER_INVOKE(##__VA_ARGS__), BINDING_DESTRUCTOR_BUILDER_INFO(##__VA_ARGS__)
#else
#define BINDING_DESTRUCTOR(...) BINDING_DESTRUCTOR_BUILDER_INVOKE(##__VA_ARGS__)
#endif

#define BINDING_SUBSCRIPT_BUILDER_GET(T, Result, Index) TFunctionPointer<decltype(&TSubscriptBuilder<T, Result, Index>::Get)>(&TSubscriptBuilder<T, Result, Index>::Get).Value.Pointer

#define BINDING_SUBSCRIPT_BUILDER_SET(T, Result, Index) TFunctionPointer<decltype(&TSubscriptBuilder<T, Result, Index>::Set)>(&TSubscriptBuilder<T, Result, Index>::Set).Value.Pointer

#define BINDING_SUBSCRIPT_BUILDER_INFO(T, Result, Index) TSubscriptBuilder<T, Result, Index>::Info()

#if WITH_FUNCTION_INFO
#define BINDING_SUBSCRIPT(T, Result, Index) BINDING_SUBSCRIPT_BUILDER_GET(T, Result, Index), BINDING_SUBSCRIPT_BUILDER_SET(T, Result, Index), BINDING_SUBSCRIPT_BUILDER_INFO(T, Result, Index)
#else
#define BINDING_SUBSCRIPT(T, Result, Index) BINDING_SUBSCRIPT_BUILDER_GET(T, Result, Index), BINDING_SUBSCRIPT_BUILDER_SET(T, Result, Index)
#endif

#define OPERATOR_BUILDER(Name, FunctionName, ImplementationName) \
TClassBuilder& Name() \
{ \
	Function(FunctionName, ImplementationName, BINDING_FUNCTION(&Name##Implementation)); \
	return *this; \
}

#define PREFIX_UNARY_CONST_OPERATOR(Name, FunctionName, ImplementationName, Operator) \
public: \
OPERATOR_BUILDER(Name, FunctionName, ImplementationName) \
private: \
static auto Name##Implementation(const T& In) \
{ \
	return Operator In; \
}

#define PREFIX_UNARY_OPERATOR(Name, FunctionName, ImplementationName, Operator) \
public: \
OPERATOR_BUILDER(Name, FunctionName, ImplementationName) \
private: \
static T& Name##Implementation(T& In) \
{ \
	return Operator In; \
}

#define BINARY_OPERATOR(Name, FunctionName, ImplementationName, Operator) \
public: \
OPERATOR_BUILDER(Name, FunctionName, ImplementationName) \
private: \
static auto Name##Implementation(const T& InA, const T& InB) \
{ \
	return InA Operator InB; \
}
