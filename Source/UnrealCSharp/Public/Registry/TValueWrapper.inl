#pragma once

template <typename T>
struct TValueWrapper
{
	typedef T Type;

	explicit TValueWrapper(const Type& InValue):
		Value(InValue)
	{
	}

	Type Value;
};
