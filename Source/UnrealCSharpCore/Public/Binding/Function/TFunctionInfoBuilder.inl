#pragma once

#include "TFunctionInfo.inl"

template <typename Builder, auto FunctionType, typename Result, typename... Args>
struct TFunctionInfoBuilder
{
	template <typename... Params>
	static auto Info(Params&&... InParams)
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>::Get(std::forward<Params>(InParams)...);
	}
};
