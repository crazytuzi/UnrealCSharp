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
	template <typename Class, size_t... Index>
	static void Call(std::index_sequence<Index...>, BINDING_CONSTRUCTOR_SIGNATURE)
	{
		std::tuple<TArgument<Args, Args>...> Argument(Array_Get(InValue, Index)...);

		auto Value = new Class(std::forward<Args>(std::get<Index>(Argument).Get())...);

		TOut<std::tuple<TArgument<Args, Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();

		if constexpr (TIsScriptStruct<Class>::Value)
		{
			FCSharpEnvironment::GetEnvironment().Bind(TBaseStructure<Class>::Get(), false);

			FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<Class>::Get(), Value, InMonoObject);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddBindingReference(InMonoObject, Value);
		}
	}
};
