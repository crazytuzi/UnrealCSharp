#pragma once

#include "TDefaultArgument.inl"

template <typename... Args>
struct TDefaultArguments
{
	template <auto SkipCount, auto Position, auto ArgumentsCount, typename... Arguments>
	struct TDefaultArgumentsBuilder;

	template <auto SkipCount, auto Position, auto ArgumentsCount, typename Argument, typename... Arguments>
	struct TDefaultArgumentsBuilder<SkipCount, Position, ArgumentsCount, Argument, Arguments...> :
		TDefaultArgumentsBuilder<SkipCount - 1, Position + 1, ArgumentsCount, Arguments...>
	{
	};

	template <auto Position, auto ArgumentsCount, typename Argument, typename... Arguments>
	struct TDefaultArgumentsBuilder<0, Position, ArgumentsCount, Argument, Arguments...>
	{
		template <class DefaultArgument, class... DefaultArguments>
		static auto Set(TArray<FString>& OutValue,
		                DefaultArgument InDefaultArgument,
		                DefaultArguments&&... InDefaultArguments)
		{
			if constexpr (Position <= ArgumentsCount)
			{
				OutValue.Add(TDefaultArgument<Argument, Argument>::Get(InDefaultArgument));
			}

			TDefaultArgumentsBuilder<0, Position + 1, ArgumentsCount, Arguments...>::Set(
				OutValue, std::forward<DefaultArguments>(InDefaultArguments)...);
		}
	};

	template <auto Position, auto ArgumentsCount>
	struct TDefaultArgumentsBuilder<0, Position, ArgumentsCount>
	{
		static auto Set(TArray<FString>& OutValue)
		{
		}
	};

	template <typename... DefaultArguments>
	static auto Get(DefaultArguments&&... InDefaultArguments)
	{
		TArray<FString> Value;

		TDefaultArgumentsBuilder<sizeof...(Args) - sizeof...(DefaultArguments),
		                         0,
		                         sizeof...(Args),
		                         std::decay_t<Args>...>::Set(
			Value, std::forward<DefaultArguments>(InDefaultArguments)...);

		return Value;
	}
};
