#pragma once

#include "TClassBuilder.inl"
#include "Template/TIsReflection.inl"

template <typename T>
class TBindingClassBuilder final : public TClassBuilder<T>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
		TClassBuilder<T>(InImplementationNameSpace)
	{
		if constexpr (!TIsReflection<T>::Value)
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				TClassBuilder<T>::Constructor(BINDING_CONSTRUCTOR(T));
			}

			TClassBuilder<T>::Destructor(BINDING_DESTRUCTOR());
		}
	}

	template <typename Class>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		static_assert(!TIsReflection<T>::Value);

		TClassBuilder<T>::GetBindingClass()->Inheritance(TClassName<Class>::Get(), InImplementationNameSpace,
		                                                 TTypeInfo<Class>::Get());

		return *this;
	}

	virtual bool IsReflection() const override
	{
		return TIsReflection<T>::Value;
	}
};
