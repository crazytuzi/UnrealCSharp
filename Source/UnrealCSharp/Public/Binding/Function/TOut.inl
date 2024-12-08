#pragma once

template <typename Type>
struct TOut
{
	explicit TOut(uint8* OutBuffer, Type& InArgument):
		Buffer(OutBuffer),
		Argument(InArgument),
		Count(0)
	{
	}

	template <auto Index>
	auto Initialize() -> TOut&
	{
		// if (Count > 0)
		// {
		// 	*OutValue = (MonoObject*)FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(), Count);
		//
		// 	Count = 0;
		// }

		return *this;
	}

	template <auto Index, typename T, typename... Args>
	auto Initialize() -> TOut&
	{
		if (std::get<Index>(Argument).IsRef())
		{
			++Count;
		}

		return Initialize<Index + 1, Args...>();
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

	int32 Count;
};
