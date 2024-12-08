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
struct TBufferSize
{
	TBufferSize()
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
		std::get<Index>(Value) = Index ? TTypeInfo<std::decay_t<T>>::Get()->GetBufferSize() : 0;

		Get<Index + 1, Args1...>();
	}

	typename TSizeTypeTuple<int32, sizeof...(Args0)>::Type Value;
};
