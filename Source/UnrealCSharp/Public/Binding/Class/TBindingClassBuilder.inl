#pragma once

#include "TClassBuilder.inl"

template <typename T>
class TBindingClassBuilder final : public TClassBuilder<T>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
		TClassBuilder<T>(InImplementationNameSpace)
	{
		if constexpr (std::is_default_constructible_v<T>)
		{
			TClassBuilder<T>::Constructor(BINDING_CONSTRUCTOR(T));
		}

		TClassBuilder<T>::Destructor(BINDING_DESTRUCTOR());
	}

	template <typename Class>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		TClassBuilder<T>::GetBindingClass()->Inheritance(TClassName<Class>::Get(), InImplementationNameSpace,
		                                                 TTypeInfo<Class>::Get());

		return *this;
	}
};
