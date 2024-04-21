#pragma once

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
				if constexpr (std::is_same_v<Argument, bool>)
				{
					OutValue.Add(InDefaultArgument ? TEXT("true") : TEXT("false"));
				}
				else if constexpr (std::is_same_v<Argument, int8> ||
					std::is_same_v<Argument, int16> ||
					std::is_same_v<Argument, int32> ||
					std::is_same_v<Argument, uint8> ||
					std::is_same_v<Argument, uint16> ||
					std::is_same_v<Argument, uint32>)
				{
					OutValue.Add(FString::Printf(TEXT("%d"), InDefaultArgument));
				}
				else if constexpr (std::is_same_v<Argument, int64> ||
					std::is_same_v<Argument, uint64>)
				{
					OutValue.Add(FString::Printf(TEXT("%lld"), InDefaultArgument));
				}
				else if constexpr (std::is_same_v<Argument, float>)
				{
					OutValue.Add(FString::Printf(TEXT("%sf"), *FString::SanitizeFloat(InDefaultArgument)));
				}
				else if constexpr (std::is_same_v<Argument, double>)
				{
					OutValue.Add(FString::SanitizeFloat(InDefaultArgument));
				}
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
