#pragma once

#include "Binding/TypeInfo/TTypeInfo.inl"

template <typename T, auto N>
struct TSizeTypeTuple
{
	using Type = decltype(std::tuple_cat(std::tuple<T>(), typename TSizeTypeTuple<T, N - 1>::Type()));
};

template <typename T>
struct TSizeTypeTuple<T, 0>
{
	using Type = std::tuple<>;
};

template <typename... Args0>
struct TBufferOffset
{
	typedef int32 TBufferOffsetType;

	TBufferOffset():
		Offset(0)
	{
		Get<0, Args0...>();
	}

	auto operator()()
	{
		return Value;
	}

	template <auto Index>
	static auto Get()
	{
	}

	template <auto Index, typename T, typename... Args1>
	auto Get()
	{
		std::get<Index>(Value) = Offset;

		Offset += TTypeInfo<std::decay_t<T>>::Get()->GetBufferSize();

		Get<Index + 1, Args1...>();
	}

	TBufferOffsetType Offset;

	typename TSizeTypeTuple<TBufferOffsetType, sizeof...(Args0)>::Type Value;
};
