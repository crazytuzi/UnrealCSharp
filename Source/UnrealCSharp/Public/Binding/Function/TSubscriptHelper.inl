#pragma once

#include "TArgument.inl"
#include "Environment/FCSharpEnvironment.h"

extern MonoObject* Array_Get(MonoArray* InMonoArray, const size_t InIndex);

template <typename Result, typename Index>
struct TSubscriptHelper
{
	template <typename Class>
	static void Get(BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			*ReturnValue = TReturnValue<Result>(std::forward<Result>(
				FoundObject->operator[](TArgument<Index, Index>(Array_Get(InValue, 0)).Get())
			)).Get();
		}
	}

	template <typename Class>
	static void Set(BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			FoundObject->operator[](TArgument<Index, Index>(Array_Get(InValue, 0)).Get()) =
				TArgument<Result, Result>(Array_Get(InValue, 1)).Get();
		}
	}
};
