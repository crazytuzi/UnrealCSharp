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

	template <auto Index>
	auto Initialize() -> TOut&
	{
		if (Count > 0)
		{
			*OutValue = (MonoObject*)FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(), Count);

			Count = 0;
		}

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

			ARRAY_SET((MonoArray*)*OutValue, MonoObject*, Count++, Value);
		}

		Get<Index + 1, Args...>();
	}

private:
	MonoObject** OutValue;

	Type& Argument;

	int32 Count;
};
