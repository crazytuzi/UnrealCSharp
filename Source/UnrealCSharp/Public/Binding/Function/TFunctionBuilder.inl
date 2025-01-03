#pragma once

#include "TFunctionHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename T, T>
struct TFunctionBuilder
{
};

template <typename Result, typename... Args, Result (*Function)(Args...)>
struct TFunctionBuilder<Result (*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (*)(Args...), Function>,
	                     EFunctionType::Static, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, std::tuple<Args...>>>::Call(
			Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...)>
struct TFunctionBuilder<Result (Class::*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (Class::*)(Args...), Function>,
	                     EFunctionType::Member, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
			Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...) const>
struct TFunctionBuilder<Result (Class::*)(Args...) const, Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (Class::*)(Args...) const, Function>,
	                     EFunctionType::Member, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
			Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};
