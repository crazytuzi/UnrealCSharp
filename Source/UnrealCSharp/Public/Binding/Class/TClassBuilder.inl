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
		FBindingClassBuilder(TClassName<T>::Get(), TTypeInfo<T>::Get(), InImplementationNameSpace),
#else
		FBindingClassBuilder(TClassName<T>::Get(), InImplementationNameSpace),
#endif
		ConstructorCount(0)
	{
	}

#if WITH_FUNCTION_INFO
	TClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo = nullptr)
#else
	TClassBuilder& Constructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(FString::Printf(TEXT(
			         "%s%d"),
		                         *TClassName<T>::Get(),
		                         ConstructorCount++
		         )
		         , InMethod, InFunctionInfo);
#else
		Function(FString::Printf(TEXT(
					 "%s%d"),
								 *TClassName<T>::Get(),
								 ConstructorCount++
				 )
				 , InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TClassBuilder& Destructor(const void* InMethod, FFunctionInfo* InFunctionInfo = nullptr)
#else
	TClassBuilder& Destructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(FUNCTION_DESTRUCTOR, InMethod, InFunctionInfo);
#else
		Function(FUNCTION_DESTRUCTOR, InMethod);
#endif

		return *this;
	}

private:
	int32 ConstructorCount;
};
