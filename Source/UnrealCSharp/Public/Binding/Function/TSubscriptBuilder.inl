#pragma once

#include "TSubscriptHelper.inl"
#include "Binding/Function/TFunctionInfoBuilder.inl"

template <typename Class, typename Result, typename Index>
struct TSubscriptBuilder :
	TFunctionInfoBuilder<TSubscriptBuilder<Class, Result, Index>, EFunctionType::Member, Result, Index>
{
	static void Invoke()
	{
	}

	static void Get(BINDING_SUBSCRIPT_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Get<Class>(BINDING_SUBSCRIPT_PARAM);
	}

	static void Set(BINDING_SUBSCRIPT_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Set<Class>(BINDING_SUBSCRIPT_PARAM);
	}
};
