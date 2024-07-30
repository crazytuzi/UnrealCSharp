#pragma once

#include "CoreMacro/BindingMacro.h"

#if WITH_FUNCTION_INFO
template <typename FunctionType, typename InfoType>
#else
template <typename FunctionType>
#endif
struct TOverloadBuilder
{
#if WITH_FUNCTION_INFO
	static auto GetImplementation(TArray<TPair<FunctionType, InfoType>>& OutValue)
	{
	}

	template <typename Function, typename Info, typename... Args>
	static auto GetImplementation(TArray<TPair<FunctionType, InfoType>>& OutValue,
	                              Function InFunction,
	                              Info InInfo,
	                              Args&&... InParams)
	{
		OutValue.Add({InFunction, InInfo});

		GetImplementation(OutValue, InParams...);
	}

	template <typename... Args>
	static auto Get(Args&&... InParams) -> const TArray<TPair<FunctionType, InfoType>>&
	{
		static TArray<TPair<FunctionType, InfoType>> Value;

		GetImplementation(Value, InParams...);

		return Value;
	}
#else
	static auto GetImplementation(TArray<FunctionType>& OutValue)
	{
	}

	template <typename Function, typename... Args>
	static auto GetImplementation(TArray<FunctionType>& OutValue,
	                              Function InFunction,
	                              Args&&... InParams)
	{
		OutValue.Add(InFunction);

		GetImplementation(OutValue, InParams...);
	}

	template <typename... Args>
	static auto Get(Args&&... InParams) -> const TArray<FunctionType>&
	{
		static TArray<FunctionType> Value;

		GetImplementation(Value, InParams...);

		return Value;
	}
#endif
};
