#pragma once

#include "TConstructorHelper.inl"
#include "Binding/Function/TFunctionInfo.inl"

template <typename Class, typename... Args>
struct TConstructorBuilder
{
	static FFunctionInfo* Info()
	{
		return TFunctionInfo<EFunctionType::Constructor, void, Args...>::Get();
	}

	static void Invoke(BINDING_CONSTRUCTOR_PLACEHOLDER_SIGNATURE)
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
