#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "Environment/FCSharpEnvironment.h"

extern MonoObject* Get(MonoArray* InMonoArray, const SIZE_T InIndex);

template <typename>
struct TConstructorHelper
{
};

template <typename... Args>
struct TConstructorHelper<TTuple<Args...>>
{
	template <typename Class, SIZE_T... Index>
	static void Call(TIntegerSequence<SIZE_T, Index...>, BINDING_CONSTRUCTOR_SIGNATURE)
	{
		TTuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

		auto Value = new Class(Forward<Args>(Argument.template Get<Index>().Get())...);

		TOut<TTuple<TArgument<Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();

		FCSharpEnvironment::GetEnvironment().AddBindingReference(InMonoObject, Value);
	}
};
