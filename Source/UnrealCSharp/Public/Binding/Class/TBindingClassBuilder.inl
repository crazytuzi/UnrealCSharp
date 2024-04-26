#pragma once

#include "TClassBuilder.inl"
#include "Template/TIsReflectionClass.inl"

template <typename T, bool bIsEngineClass0 = false>
class TBindingClassBuilder final : public TClassBuilder<T, bIsEngineClass0>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
		TClassBuilder<T, bIsEngineClass0>(InImplementationNameSpace)
	{
		if constexpr (!TIsReflectionClass<T>::Value)
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				TClassBuilder<T, bIsEngineClass0>::Constructor(BINDING_CONSTRUCTOR(T));
			}

			TClassBuilder<T, bIsEngineClass0>::Destructor(BINDING_DESTRUCTOR());
		}
	}

	template <typename Class, bool bIsEngineClass1 = false>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		TClassBuilder<T, bIsEngineClass0>::ClassRegister->Inheritance({[]() { return TName<Class, Class>::Get(); }},
		                                                              InImplementationNameSpace,
		                                                              {
			                                                              []()
			                                                              {
				                                                              return TIsEngineClass<
					                                                              T, bIsEngineClass1>::Get();
			                                                              }
		                                                              },
		                                                              TIsReflectionClass<Class>::Value
#if WITH_TYPE_INFO
		                                                              , {[]() { return TTypeInfo<Class>::Get(); }}
#endif
		);

		return *this;
	}
};
