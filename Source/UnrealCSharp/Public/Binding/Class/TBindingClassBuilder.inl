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
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace, TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
		Constructor(BINDING_CONSTRUCTOR(T));

		Destructor(BINDING_DESTRUCTOR());
	}

	template <typename Class>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		GetBindingClass()->Inheritance(TClassFullName<Class>::Get(), InImplementationNameSpace,
		                               TTypeInfo<Class>::Get());

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
};
