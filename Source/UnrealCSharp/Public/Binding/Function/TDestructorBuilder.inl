#pragma once

#include "TDestructorHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename... Args>
struct TDestructorBuilder :
	TFunctionInfoBuilder<TDestructorBuilder<Args...>, EFunctionType::Destructor, void, Args...>
{
	static void Invoke(BINDING_DESTRUCTOR_SIGNATURE)
	{
		TDestructorHelper<std::tuple<Args...>>::template Call(
			std::make_index_sequence<sizeof...(Args)>(), BINDING_DESTRUCTOR_PARAM);
	}
};
