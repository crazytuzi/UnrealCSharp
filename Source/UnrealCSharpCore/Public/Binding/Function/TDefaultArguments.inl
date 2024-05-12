#pragma once

#include "TDefaultArgument.inl"

template <typename... Args>
struct TDefaultArguments
{
	template <int SkipCount, int Position, int ArgumentsCount, typename... Arguments>
	struct TDefaultArgumentsBuilder;

	template <int SkipCount, int Position, int ArgumentsCount, typename Argument, typename... Arguments>
	struct TDefaultArgumentsBuilder<SkipCount, Position, ArgumentsCount, Argument, Arguments...> :
		TDefaultArgumentsBuilder<SkipCount - 1, Position + 1, ArgumentsCount, Arguments...>
	{
	};

	template <int Position, int ArgumentsCount, typename Argument, typename... Arguments>
	struct TDefaultArgumentsBuilder<0, Position, ArgumentsCount, Argument, Arguments...>
	{
		template <class DefaultArgument, class... DefaultArguments>
		static void Set(TArray<FString>& OutValue,
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

	template <int Position, int ArgumentsCount>
	struct TDefaultArgumentsBuilder<0, Position, ArgumentsCount>
	{
		static void Set(TArray<FString>& OutValue)
		{
		}
	};

	template <typename... DefaultArguments>
	static TArray<FString> Get(DefaultArguments&&... InDefaultArguments)
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
