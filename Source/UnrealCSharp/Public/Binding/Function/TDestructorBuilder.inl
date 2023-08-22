#pragma once

#include "TDestructorHelper.inl"
#include "Binding/Function/TFunctionInfo.inl"

template <typename... Args>
struct TDestructorBuilder
{
	static FFunctionInfo* Info()
	{
		return TFunctionInfo<EFunctionType::Destructor, void>::Get();
	}

	static void Invoke(BINDING_FUNCTION_SIGNATURE)
	{
		TDestructorHelper<TTuple<Args...>>::template Call(
			TMakeIntegerSequence<SIZE_T, sizeof...(Args)>(), BINDING_FUNCTION_PARAM);
	}
};
