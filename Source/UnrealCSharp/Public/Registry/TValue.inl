#pragma once

template <typename T>
struct TValue
{
	typedef T Type;

	explicit TValue(Type InValue):
		Value(InValue)
	{
	}

	Type Value;
};
