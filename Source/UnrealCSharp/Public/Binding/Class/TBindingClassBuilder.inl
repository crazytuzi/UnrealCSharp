#pragma once

#include "TOperatorClassBuilder.inl"

template <typename T>
class TBindingClassBuilder final : public TOperatorClassBuilder<T>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
		TOperatorClassBuilder<T>(InImplementationNameSpace)
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
		TOperatorClassBuilder<T>::GetBindingClass()->Inheritance(TClassName<Class>::Get(), TClassFullName<Class>::Get(),
		                                                         InImplementationNameSpace, TTypeInfo<Class>::Get());

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Constructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		TOperatorClassBuilder<T>::Function(TClassFullName<T>::Get(), InMethod, InFunctionInfo);
#else
		TOperatorClassBuilder<T>::Function(TClassFullName<T>::Get(), InMethod);
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
		TOperatorClassBuilder<T>::Function(FString::Printf(TEXT(
			                                   "~%s"
		                                   ),
		                                                   *TClassFullName<T>::Get()
		                                   ),
		                                   FUNCTION_DESTRUCTOR,
		                                   InMethod,
		                                   InFunctionInfo);
#else
		TOperatorClassBuilder<T>::Function(FString::Printf(TEXT(
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
