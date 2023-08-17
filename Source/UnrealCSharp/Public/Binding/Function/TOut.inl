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

	template <SIZE_T Index>
	TOut& Initialize()
	{
		if (Count > 0)
		{
			*OutValue = (MonoObject*)FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(), Count);

			Count = 0;
		}

		return *this;
	}

	template <SIZE_T Index, typename T, typename... Args>
	TOut& Initialize()
	{
		if (Argument.template Get<Index>().IsOut())
		{
			++Count;
		}

		return Initialize<Index + 1, Args...>();;
	}

	template <SIZE_T Index>
	static void Get()
	{
	}

	template <SIZE_T Index, typename T, typename... Args>
	void Get()
	{
		if (Argument.template Get<Index>().IsOut())
		{
			auto Value = Argument.template Get<Index>().Set();

			ARRAY_SET((MonoArray*)*OutValue, MonoObject*, Count++, Value);
		}

		Get<Index + 1, Args...>();
	}

private:
	MonoObject** OutValue;

	Type& Argument;

	int32 Count;
};
