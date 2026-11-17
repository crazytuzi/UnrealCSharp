#pragma once

template <typename Result, typename... Args>
static constexpr auto TGetFunctionParamCount(Result (*)(Args...))
{
	return sizeof...(Args);
}

template <typename T>
static constexpr auto TGetFunctionParamCount(T)
{
	return INDEX_NONE;
}
