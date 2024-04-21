#pragma once

#include "TFunctionInfo.inl"

template <typename Builder, EFunctionType FunctionType, typename Result, typename... Args>
struct TFunctionInfoBuilder
{
	template <typename... Params>
	static FFunctionInfo* Info(Params&&... InParams)
	{
		return TFunctionInfo<&Builder::Invoke, FunctionType, Result, Args...>::Get(std::forward<Params>(InParams)...);
	}
};
