#pragma once

#include "TFunctionHelper.inl"
#include "THasRef.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename T, T>
struct TFunctionBuilder
{
};

template <typename... Args, void (*Function)(Args...)>
struct TFunctionBuilder<void (*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<void (*)(Args...), Function>,
	                     EFunctionType::Static, void, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};

template <typename Result, typename... Args, Result (*Function)(Args...)>
struct TFunctionBuilder<Result (*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (*)(Args...), Function>,
	                     EFunctionType::Static, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::Call(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};

template <typename Class, typename... Args, void (Class::*Function)(Args...)>
struct TFunctionBuilder<void (Class::*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<void (Class::*)(Args...), Function>,
	                     EFunctionType::Member, void, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...)>
struct TFunctionBuilder<Result (Class::*)(Args...), Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (Class::*)(Args...), Function>,
	                     EFunctionType::Member, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};

template <typename Class, typename... Args, void (Class::*Function)(Args...) const>
struct TFunctionBuilder<void (Class::*)(Args...) const, Function> :
	TFunctionInfoBuilder<TFunctionBuilder<void (Class::*)(Args...) const, Function>,
	                     EFunctionType::Member, void, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			TFunctionHelper<TPair<void, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...) const>
struct TFunctionBuilder<Result (Class::*)(Args...) const, Function> :
	TFunctionInfoBuilder<TFunctionBuilder<Result (Class::*)(Args...) const, Function>,
	                     EFunctionType::Member, Result, Args...>
{
	static auto Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
	{
		if constexpr (sizeof...(Args) == 0)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM0);
		}
		else if constexpr (!THasRef<Args...>::Value)
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM2);
		}
		else
		{
			return TFunctionHelper<TPair<Result, std::tuple<Args...>>>::template Call<Class>(
				Function, std::make_index_sequence<sizeof...(Args)>(), BINDING_FUNCTION_PLACEHOLDER_PARAM3);
		}
	}
};
