#pragma once

#include "TArgument.inl"
#include "TBufferOffset.inl"
#include "TOut.inl"
#include "TReturnValue.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/SignatureMacro.h"

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
		std::tuple<TArgument<Args, Args>...> Argument(IN_BUFFER + std::get<Index>(TBufferOffset<Args...>()())...);

		if constexpr (std::is_same_v<Result, void>)
		{
			InFunction(std::forward<Args>(std::get<Index>(Argument).Get())...);
		}
		else
		{
			TReturnValue<Result>(RETURN_BUFFER, std::forward<Result>(InFunction(
				                     std::forward<Args>(std::get<Index>(Argument).Get())...)));
		}

		TOut<std::tuple<TArgument<Args, Args>...>, Args...>(OUT_BUFFER, Argument);
	}

	template <typename Class, typename Function, auto... Index>
	static auto Call(Function InFunction, std::index_sequence<Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			std::tuple<TArgument<Args, Args>...> Argument(
				IN_BUFFER + std::get<Index>(TBufferOffset<Args...>()())...);

			if constexpr (std::is_same_v<Result, void>)
			{
				(FoundObject->*InFunction)(std::forward<Args>(std::get<Index>(Argument).Get())...);
			}
			else
			{
				TReturnValue<Result>(RETURN_BUFFER, std::forward<Result>((FoundObject->*InFunction)(
					                     std::forward<Args>(std::get<Index>(Argument).Get())...)));
			}

			TOut<std::tuple<TArgument<Args, Args>...>, Args...>(OUT_BUFFER, Argument);
		}
	}
};
