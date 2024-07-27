#pragma once

template <typename T, auto Size>
static constexpr auto TGetArrayLength(T (&)[Size])
{
	return Size;
}

template <typename T>
static constexpr auto TGetArrayLength(T)
{
	return 1;
}
