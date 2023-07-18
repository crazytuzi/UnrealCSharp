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

	static void Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TConstructorHelper<TTuple<Args...>>::template Call<Class>(
			TMakeIntegerSequence<SIZE_T, sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};
