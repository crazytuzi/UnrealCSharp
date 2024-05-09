#pragma once

template <typename T, typename Enable = void>
struct TDefaultArgument
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static FString Get(const uint8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static FString Get(const uint16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static FString Get(const uint32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static FString Get(const uint64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static FString Get(const int8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static FString Get(const int16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static FString Get(const int32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static FString Get(const int64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static FString Get(const bool InValue)
	{
		return InValue ? TEXT("true") : TEXT("false");
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static FString Get(const float InValue)
	{
		return FString::Printf(TEXT("%sf"), *FString::SanitizeFloat(InValue));
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static FString Get(const double InValue)
	{
		return FString::SanitizeFloat(InValue);
	}
};
