#pragma once

template <typename Type, typename... Args0>
struct TOut
{
	explicit TOut(uint8* OutBuffer, Type& InArgument):
		Buffer(OutBuffer),
		Argument(InArgument)
	{
		Get<0, Args0...>();
	}

	template <auto Index>
	static auto Get()
	{
	}

	template <auto Index, typename T, typename... Args>
	auto Get()
	{
		if (std::get<Index>(Argument).IsRef())
		{
			auto Value = std::get<Index>(Argument).Set();

			if constexpr (TIsPrimitive<T>::Value)
			{
				*(std::remove_const_t<std::decay_t<T>>*)Buffer = Value;
			}
			else
			{
				*reinterpret_cast<void**>(Buffer) = Value;
			}

			Buffer += TTypeInfo<std::decay_t<T>>::Get()->GetBufferSize();
		}

		Get<Index + 1, Args...>();
	}

private:
	uint8* Buffer;

	Type& Argument;
};
