#pragma once

#include "TClassBuilder.inl"
#include "Template/TIsReflectionClass.inl"

template <typename T, auto IsProjectClass0 = true>
class TBindingClassBuilder final : public TClassBuilder<T, IsProjectClass0>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace,
	                              const TOptional<TFunction<FString()>>& InClassFunction = {}):
		TClassBuilder<T, IsProjectClass0>(InImplementationNameSpace, InClassFunction)
	{
		if constexpr (!TIsReflectionClass<T>::Value)
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				TClassBuilder<T, IsProjectClass0>::Constructor(BINDING_CONSTRUCTOR(T));
			}

			TClassBuilder<T, IsProjectClass0>::Destructor(BINDING_DESTRUCTOR());
		}
	}

	template <typename Class, auto IsProjectClass1 = false>
	auto Inheritance(const FString& InImplementationNameSpace) -> TBindingClassBuilder&
	{
		TClassBuilder<T, IsProjectClass0>::ClassRegister->Inheritance({[]() { return TName<Class, Class>::Get(); }},
		                                                              InImplementationNameSpace,
		                                                              {
			                                                              []()
			                                                              {
				                                                              return TIsProjectClass<
					                                                              T, IsProjectClass1>::Get();
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
