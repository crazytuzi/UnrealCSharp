#pragma once

#include "TFunctionHelper.inl"
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

template <typename Result, typename... Args, Result (*Function)(Args...)>
struct TFunctionBuilder<Result (*)(Args...), Function> :
	TFunctionInfoBuilder<EFunctionType::Static, Result, Args...>
{
	static void Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, TTuple<Args...>>>::Call(
			Function, TMakeIntegerSequence<SIZE_T, sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...)>
struct TFunctionBuilder<Result (Class::*)(Args...), Function> :
	TFunctionInfoBuilder<EFunctionType::Member, Result, Args...>
{
	static void Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, TTuple<Args...>>>::template Call<Class>(
			Function, TMakeIntegerSequence<SIZE_T, sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};

template <typename Class, typename Result, typename... Args, Result (Class::*Function)(Args...) const>
struct TFunctionBuilder<Result (Class::*)(Args...) const, Function> :
	TFunctionInfoBuilder<EFunctionType::Member, Result, Args...>
{
	static void Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TFunctionHelper<TPair<Result, TTuple<Args...>>>::template Call<Class>(
			Function, TMakeIntegerSequence<SIZE_T, sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};
