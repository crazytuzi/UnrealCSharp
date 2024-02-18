#pragma once

template <typename T>
struct TFunctionPointer
{
	explicit TFunctionPointer(const T& InFunction)
	{
		Value.Function = InFunction;
	}

	union
	{
		T Function;

		void* Pointer;
	} Value;
};
