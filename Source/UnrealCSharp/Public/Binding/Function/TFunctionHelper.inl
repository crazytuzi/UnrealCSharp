#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "TReturnValue.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/SignatureMacro.h"

inline MonoObject* Array_Get(MonoArray* InMonoArray, const size_t InIndex)
{
	return ARRAY_GET(InMonoArray, MonoObject*, InIndex);
}

template <typename>
struct TFunctionHelper
{
};

template <typename Result, typename... Args>
struct TFunctionHelper<TPair<Result, std::tuple<Args...>>>
{
	template <typename Function, auto... Index>
	static auto Call(Function InFunction, std::index_sequence<Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		MonoObject* ReturnValue{};

		std::tuple<TArgument<Args, Args>...> Argument(Array_Get(InValue, Index)...);

		if constexpr (std::is_same_v<Result, void>)
		{
			InFunction(std::forward<Args>(std::get<Index>(Argument).Get())...);
		}
		else
		{
			ReturnValue = TReturnValue<Result>(std::forward<Result>(
					InFunction(std::forward<Args>(std::get<Index>(Argument).Get())...)))
				.Get();
		}

		TOut<std::tuple<TArgument<Args, Args>...>>(OutValue, Argument)
			.template Initialize<0, Args...>()
			.template Get<0, Args...>();

		return ReturnValue;
	}

	template <typename Class, typename Function, auto... Index>
	static auto Call(Function InFunction, std::index_sequence<Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		MonoObject* ReturnValue{};

		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			std::tuple<TArgument<Args, Args>...> Argument(Array_Get(InValue, Index)...);

			if constexpr (std::is_same_v<Result, void>)
			{
				(FoundObject->*InFunction)(std::forward<Args>(std::get<Index>(Argument).Get())...);
			}
			else
			{
				ReturnValue = TReturnValue<Result>(std::forward<Result>(
						(FoundObject->*InFunction)(std::forward<Args>(std::get<Index>(Argument).Get())...)))
					.Get();
			}

			TOut<std::tuple<TArgument<Args, Args>...>>(OutValue, Argument)
				.template Initialize<0, Args...>()
				.template Get<0, Args...>();
		}

		return ReturnValue;
	}
};
