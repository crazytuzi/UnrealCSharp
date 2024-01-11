#pragma once

template <typename Type>
struct TOut
{
	explicit TOut(MonoObject** InOutValue, Type& InArgument):
		OutValue(InOutValue),
		Argument(InArgument),
		Count(0)
	{
	}

	template <size_t Index>
	TOut& Initialize()
	{
		if (Count > 0)
		{
			*OutValue = (MonoObject*)FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(), Count);

			Count = 0;
		}

		return *this;
	}

	template <size_t Index, typename T, typename... Args>
	TOut& Initialize()
	{
		if (std::get<Index>(Argument).IsRef())
		{
			++Count;
		}

		return Initialize<Index + 1, Args...>();
	}

	template <size_t Index>
	static void Get()
	{
	}

	template <size_t Index, typename T, typename... Args>
	void Get()
	{
		if (std::get<Index>(Argument).IsRef())
		{
			auto Value = std::get<Index>(Argument).Set();

			ARRAY_SET((MonoArray*)*OutValue, MonoObject*, Count++, Value);
		}

		Get<Index + 1, Args...>();
	}

private:
	MonoObject** OutValue;

	Type& Argument;

	int32 Count;
};
