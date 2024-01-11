#pragma once

#include "TFunctionHelper.inl"
#include "THasRef.inl"
#include "Binding/Function/TFunctionInfo.inl"

template <typename T, T>
struct TFunctionBuilder
{
};

template <EFunctionType FunctionType, typename Result, typename... Args>
struct TFunctionInfoBuilder
{
	static FFunctionInfo* Info()
	{
		return TFunctionInfo<FunctionType, Result, Args...>::Get();
	}
};

template <typename... Args, void (*Function)(Args...)>
struct TFunctionBuilder<void (*)(Args...), Function> :
	TFunctionInfoBuilder<EFunctionType::Static, void, Args...>
{
	static void Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
	TFunctionInfoBuilder<EFunctionType::Static, Result, Args...>
{
	static MonoObject* Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
	TFunctionInfoBuilder<EFunctionType::Member, void, Args...>
{
	static void Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
	TFunctionInfoBuilder<EFunctionType::Member, Result, Args...>
{
	static MonoObject* Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
	TFunctionInfoBuilder<EFunctionType::Member, void, Args...>
{
	static void Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
	TFunctionInfoBuilder<EFunctionType::Member, Result, Args...>
{
	static MonoObject* Invoke(BINDING_FUNCTION_PLACEHOLDER_SIGNATURE)
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
