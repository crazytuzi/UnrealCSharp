#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/SignatureMacro.h"

extern MonoObject* Array_Get(MonoArray* InMonoArray, const size_t InIndex);

template <typename>
struct TConstructorHelper
{
};

template <typename... Args>
struct TConstructorHelper<std::tuple<Args...>>
{
	template <typename Class, auto... Index>
	static auto Call(std::index_sequence<Index...>, BINDING_CONSTRUCTOR_SIGNATURE)
	{
		std::tuple<TArgument<Args, Args>...> Argument(Array_Get(InValue, Index)...);

		auto Value = new Class(std::forward<Args>(std::get<Index>(Argument).Get())...);

		TOut<std::tuple<TArgument<Args, Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();

		if constexpr (TIsScriptStruct<Class>::Value)
		{
			FCSharpEnvironment::GetEnvironment().Bind<false>(TBaseStructure<Class>::Get());

			FCSharpEnvironment::GetEnvironment().AddStructReference<true>(
				TBaseStructure<Class>::Get(), Value, InMonoObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference<Class, true>(InMonoObject, Value);
		}
	}
};
