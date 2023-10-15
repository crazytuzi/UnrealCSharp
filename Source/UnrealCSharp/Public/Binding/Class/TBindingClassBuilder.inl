#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/Template/TClassFullName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Macro/FunctionMacro.h"

template <typename T>
class TBindingClassBuilder final : public FClassBuilder
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace,
		              TClassFullName<T>::Get(), TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
		if constexpr (std::is_default_constructible_v<T>)
		{
			Constructor(BINDING_CONSTRUCTOR(T));
		}

		Destructor(BINDING_DESTRUCTOR());
	}

	template <typename Class>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		GetBindingClass()->Inheritance(TClassName<Class>::Get(), TClassFullName<Class>::Get(),
		                               InImplementationNameSpace, TTypeInfo<Class>::Get());

		return *this;
	}

	TBindingClassBuilder& EqualTo()
	{
		EqualTo(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator==));

		return *this;
	}

	TBindingClassBuilder& NotEqualTo()
	{
		NotEqualTo(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator!=));

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Constructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TClassFullName<T>::Get(), InMethod, InFunctionInfo);
#else
		Function(TClassFullName<T>::Get(), InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& Destructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Destructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(FString::Printf(TEXT(
			         "~%s"
		         ),
		                         *TClassFullName<T>::Get()
		         ),
		         FUNCTION_DESTRUCTOR,
		         InMethod,
		         InFunctionInfo);
#else
		Function(FString::Printf(TEXT(
					 "~%s"
				 ),
								 *TClassFullName<T>::Get()
				 ),
				 FUNCTION_DESTRUCTOR,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& EqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& EqualTo(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator =="),
		         FUNCTION_EQUAL_TO,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator =="),
				 FUNCTION_EQUAL_TO,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& NotEqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& NotEqualTo(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator !="),
		         FUNCTION_NOT_EQUAL_TO,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator !="),
				 FUNCTION_NOT_EQUAL_TO,
				 InMethod);
#endif

		return *this;
	}
};
