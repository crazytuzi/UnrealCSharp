#pragma once

template <typename T, int32 Size>
static constexpr int TGetArrayLength(T (&)[Size])
{
	return Size;
}

template <typename T>
static constexpr int TGetArrayLength(T)
{
	return 1;
}
