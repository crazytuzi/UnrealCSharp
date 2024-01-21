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

	static void Invoke(BINDING_DESTRUCTOR_SIGNATURE)
	{
		TDestructorHelper<std::tuple<Args...>>::template Call(
			std::make_index_sequence<sizeof...(Args)>(), BINDING_DESTRUCTOR_PARAM);
	}
};
