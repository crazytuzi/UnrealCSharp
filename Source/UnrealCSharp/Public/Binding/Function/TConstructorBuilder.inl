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

	static void Invoke(BINDING_CONSTRUCTOR_SIGNATURE)
	{
		TConstructorHelper<std::tuple<Args...>>::template Call<Class>(
			std::make_index_sequence<sizeof...(Args)>(), BINDING_CONSTRUCTOR_PARAM);
	}
};
