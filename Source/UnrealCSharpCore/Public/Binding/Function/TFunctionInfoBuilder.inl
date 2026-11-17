#pragma once

#include "TFunctionInfo.inl"

template <typename Builder, auto FunctionType, typename Result, typename... Args>
struct TFunctionInfoBuilder
{
	static auto Make()
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>();
	}

	template <typename... DefaultArguments>
	static auto Make(const TArray<FString>& InParamNames, DefaultArguments&&... InDefaultArguments)
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>(
			InParamNames, TDefaultArguments<Args...>::Get(std::forward<DefaultArguments>(InDefaultArguments)...));
	}

	static auto Make(const EFunctionInteract InFunctionInteract)
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>(InFunctionInteract);
	}

	template <typename... DefaultArguments>
	static auto Make(const TArray<FString>& InParamNames, const EFunctionInteract InFunctionInteract,
	                 DefaultArguments&&... InDefaultArguments)
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>(
			InParamNames, InFunctionInteract,
			TDefaultArguments<Args...>::Get(std::forward<DefaultArguments>(InDefaultArguments)...));
	}
};
