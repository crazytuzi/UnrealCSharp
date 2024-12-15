#pragma once

#include "CoreMacro/BufferMacro.h"
#include "TBufferOffset.inl"

template <typename Type, typename... Args0>
struct TOut
{
	explicit TOut(OUT_BUFFER_SIGNATURE, Type& InArgument) :
		Buffer(OUT_BUFFER),
		Argument(InArgument)
	{
		Get<0, Args0...>();
	}

	template <auto Index>
	static auto Get()
	{
	}

	template <auto Index, typename T, typename... Args1>
	auto Get()
	{
		if (std::get<Index>(Argument).IsRef())
		{
			if constexpr (TIsPrimitive<T>::Value)
			{
				*(std::remove_const_t<std::decay_t<T>>*)Buffer = std::get<Index>(Argument).Set();
			}
			else
			{
				*reinterpret_cast<void**>(Buffer) = std::get<Index>(Argument).Set();
			}

			Buffer += std::get<Index>(TBufferOffset<Args0...>()());
		}

		Get<Index + 1, Args1...>();
	}

private:
	uint8* Buffer;

	Type& Argument;
};
