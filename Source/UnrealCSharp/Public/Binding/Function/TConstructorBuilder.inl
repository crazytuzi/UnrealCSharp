#pragma once

#include "TConstructorHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename Class, typename... Args>
struct TConstructorBuilder :
	TFunctionInfoBuilder<TConstructorBuilder<Class, Args...>, EFunctionType::Constructor, void, Args...>
{
	static auto Invoke(BINDING_CONSTRUCTOR_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			TConstructorHelper<std::tuple<Args...>>::template Call<Class>(
				std::make_index_sequence<sizeof...(Args)>(), BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			TConstructorHelper<std::tuple<Args...>>::template Call<Class>(
				std::make_index_sequence<sizeof...(Args)>(), BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM2);
		}
		else
		{
			TConstructorHelper<std::tuple<Args...>>::template Call<Class>(
				std::make_index_sequence<sizeof...(Args)>(), BINDING_CONSTRUCTOR_PLACEHOLDER_PARAM3);
		}
	}
};
