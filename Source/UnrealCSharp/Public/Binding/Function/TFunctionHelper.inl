#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "TReturnValue.inl"
#include "Environment/FCSharpEnvironment.h"
#include "UEVersion.h"

inline MonoObject* Get(MonoArray* InMonoArray, const SIZE_T InIndex)
{
	return ARRAY_GET(InMonoArray, MonoObject*, InIndex);
}

template <typename>
struct TFunctionHelper
{
};

template <typename Result, typename... Args>
struct TFunctionHelper<TPair<Result, TTuple<Args...>>>
{
	template <typename Function, SIZE_T... Index>
	static void Call(Function InFunction, TIntegerSequence<SIZE_T, Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		TTuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

#if UE_T_IS_SAME
		if constexpr (TIsSame<Result, void>::Value)
#else
		if constexpr (std::is_same_v<Result, void>)
#endif
		{
			InFunction(Forward<Args>(Argument.template Get<Index>().Get())...);
		}
		else
		{
			*ReturnValue = TReturnValue<Result>(Forward<Result>(
					InFunction(Forward<Args>(Argument.template Get<Index>().Get())...)))
				.Get();
		}

		TOut<TTuple<TArgument<Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();
	}

	template <typename Class, typename Function, SIZE_T... Index>
	static void Call(Function InFunction, TIntegerSequence<SIZE_T, Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			TTuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

#if UE_T_IS_SAME
			if constexpr (TIsSame<Result, void>::Value)
#else
			if constexpr (std::is_same_v<Result, void>)
#endif
			{
				(FoundObject->*InFunction)(Forward<Args>(Argument.template Get<Index>().Get())...);
			}
			else
			{
				*ReturnValue = TReturnValue<Result>(Forward<Result>(
						(FoundObject->*InFunction)(Forward<Args>(Argument.template Get<Index>().Get())...)))
					.Get();
			}

			TOut<TTuple<TArgument<Args>...>>(OutValue, Argument)
				.template Initialize<0, Args...>()
				.template Get<0, Args...>();
		}
	}
};
