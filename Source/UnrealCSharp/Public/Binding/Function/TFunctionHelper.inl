#pragma once

#include "TArgument.inl"
#include "TBufferSize.inl"
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
		std::tuple<TArgument<Args, Args>...> Argument(IN_BUFFER + std::get<Index>(TBufferSize<Args...>()())...);

		if constexpr (std::is_same_v<Result, void>)
		{
			InFunction(std::forward<Args>(std::get<Index>(Argument).Get())...);
		}
		else
		{
			auto Value = TReturnValue<Result>(std::forward<Result>(
					InFunction(std::forward<Args>(std::get<Index>(Argument).Get())...)))
				.Get();

			if constexpr (TIsPrimitive<Result>::Value)
			{
				*(std::remove_const_t<std::decay_t<Result>>*)RETURN_BUFFER = Value;
			}
			else
			{
				*reinterpret_cast<void**>(RETURN_BUFFER) = Value;
			}
		}
		
		TOut<std::tuple<TArgument<Args, Args>...>, Args...>(OUT_BUFFER, Argument);
	}

	template <typename Class, typename Function, auto... Index>
	static auto Call(Function InFunction, std::index_sequence<Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			std::tuple<TArgument<Args, Args>...> Argument(IN_BUFFER + std::get<Index>(TBufferSize<Args...>()())...);
		
			if constexpr (std::is_same_v<Result, void>)
			{
				(FoundObject->*InFunction)(std::forward<Args>(std::get<Index>(Argument).Get())...);
			}
			else
			{
				auto Value = TReturnValue<Result>(std::forward<Result>(
						(FoundObject->*InFunction)(std::forward<Args>(std::get<Index>(Argument).Get())...)))
					.Get();
		
				if constexpr (TIsPrimitive<Result>::Value)
				{
					*(std::remove_const_t<std::decay_t<Result>>*)RETURN_BUFFER = Value;
				}
				else
				{
					*reinterpret_cast<void**>(RETURN_BUFFER) = Value;
				}
			}
		
			TOut<std::tuple<TArgument<Args, Args>...>, Args...>(OUT_BUFFER, Argument);
		}
	}
};
