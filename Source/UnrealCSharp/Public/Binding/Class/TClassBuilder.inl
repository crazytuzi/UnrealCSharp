#pragma once

#include "FBindingClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Macro/FunctionMacro.h"

template <typename T>
class TClassBuilder final : public FBindingClassBuilder
{
public:
	explicit TClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FBindingClassBuilder(TClassName<T>::Get(), InImplementationNameSpace, TTypeInfo<T>::Get())
#else
		FBindingClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
	}

#if WITH_FUNCTION_INFO
	TClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Constructor(const void* InMethod)
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
	TClassBuilder& Destructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Destructor(const void* InMethod)
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
