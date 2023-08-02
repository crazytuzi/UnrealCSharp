#pragma once

#include "Binding/Function/FFunctionInfo.h"

#if WITH_FUNCTION_INFO
template <typename FunctionType, typename InfoType>
#else
template <typename FunctionType>
#endif
struct TOverloadBuilder
{
#if WITH_FUNCTION_INFO
	static void GetImplementation(TArray<TPair<FunctionType, InfoType>>& OutValue)
	{
	}

	template <typename Function, typename Info, typename... Args>
	static void GetImplementation(TArray<TPair<FunctionType, InfoType>>& OutValue,
	                              Function InFunction,
	                              Info InInfo,
	                              Args&&... InParams)
	{
		OutValue.Add({InFunction, InInfo});

		GetImplementation(OutValue, InParams...);
	}

	template <typename... Args>
	static const TArray<TPair<FunctionType, InfoType>>& Get(Args&&... InParams)
	{
		static TArray<TPair<FunctionType, InfoType>> Value;

		GetImplementation(Value, InParams...);

		return Value;
	}
#else
	static void GetImplementation(TArray<FunctionType>& OutValue)
	{
	}

	template <typename Function, typename... Args>
	static void GetImplementation(TArray<FunctionType>& OutValue,
	                              Function InFunction,
	                              Args&&... InParams)
	{
		OutValue.Add(InFunction);

		GetImplementation(OutValue, InParams...);
	}

	template <typename... Args>
	static const TArray<FunctionType>& Get(Args&&... InParams)
	{
		static TArray<FunctionType> Value;

		GetImplementation(Value, InParams...);

		return Value;
	}
#endif
};
