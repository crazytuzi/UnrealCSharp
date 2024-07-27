#pragma once

#include "TClassBuilder.inl"
#include "Template/TIsReflectionClass.inl"

template <typename T, auto IsEngineClass0 = false>
class TBindingClassBuilder final : public TClassBuilder<T, IsEngineClass0>
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace,
	                              const TOptional<TFunction<FString()>>& InClassFunction = {}):
		TClassBuilder<T, IsEngineClass0>(InImplementationNameSpace, InClassFunction)
	{
		if constexpr (!TIsReflectionClass<T>::Value)
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				TClassBuilder<T, IsEngineClass0>::Constructor(BINDING_CONSTRUCTOR(T));
			}

			TClassBuilder<T, IsEngineClass0>::Destructor(BINDING_DESTRUCTOR());
		}
	}

	template <typename Class, auto IsEngineClass1 = false>
	auto Inheritance(const FString& InImplementationNameSpace) -> TBindingClassBuilder&
	{
		TClassBuilder<T, IsEngineClass0>::ClassRegister->Inheritance({[]() { return TName<Class, Class>::Get(); }},
		                                                             InImplementationNameSpace,
		                                                             {
			                                                             []()
			                                                             {
				                                                             return TIsEngineClass<
					                                                             T, IsEngineClass1>::Get();
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
