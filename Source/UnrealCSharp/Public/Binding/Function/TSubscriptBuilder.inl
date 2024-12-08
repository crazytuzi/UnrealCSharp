#pragma once

#include "TSubscriptHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename Class, typename Result, typename Index>
struct TSubscriptBuilder :
	TFunctionInfoBuilder<TSubscriptBuilder<Class, Result, Index>, EFunctionType::Member, Result, Index>
{
	static auto Invoke()
	{
	}

	static auto Get(BINDING_SUBSCRIPT_GET_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Get<Class>(BINDING_SUBSCRIPT_GET_PARAM);
	}

	static auto Set(BINDING_SUBSCRIPT_SET_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Set<Class>(BINDING_SUBSCRIPT_SET_PARAM);
	}
};
