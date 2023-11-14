#pragma once

#include "TSubscriptHelper.inl"
#include "Binding/Function/TFunctionInfo.inl"

template <typename Class, typename Result, typename Index>
struct TSubscriptBuilder
{
	static FFunctionInfo* Info()
	{
		return TFunctionInfo<EFunctionType::Member, Result, Index>::Get();
	}

	static void Get(BINDING_FUNCTION_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Get<Class>(BINDING_FUNCTION_PARAM);
	}

	static void Set(BINDING_FUNCTION_SIGNATURE)
	{
		TSubscriptHelper<Result, Index>::template Set<Class>(BINDING_FUNCTION_PARAM);
	}
};
