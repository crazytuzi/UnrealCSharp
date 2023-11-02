#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "Environment/FCSharpEnvironment.h"

extern MonoObject* Get(MonoArray* InMonoArray, const size_t InIndex);

template <typename>
struct TConstructorHelper
{
};

template <typename... Args>
struct TConstructorHelper<std::tuple<Args...>>
{
	template <typename Class, size_t... Index>
	static void Call(std::index_sequence<Index...>, BINDING_CONSTRUCTOR_SIGNATURE)
	{
		std::tuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

		auto Value = new Class(std::forward<Args>(Argument.template Get<Index>().Get())...);

		TOut<std::tuple<TArgument<Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();

		FCSharpEnvironment::GetEnvironment().AddBindingReference(InMonoObject, Value);
	}
};
