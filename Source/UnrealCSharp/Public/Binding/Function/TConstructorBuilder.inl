#pragma once

#include "TConstructorHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename Class, typename... Args>
struct TConstructorBuilder :
	TFunctionInfoBuilder<TConstructorBuilder<Class, Args...>, EFunctionType::Constructor, void, Args...>
{
	static auto Invoke(BINDING_CONSTRUCTOR_SIGNATURE)
	{
		TConstructorHelper<std::tuple<Args...>>::template Call<Class>(
			std::make_index_sequence<sizeof...(Args)>(), BINDING_CONSTRUCTOR_PARAM);
	}
};
