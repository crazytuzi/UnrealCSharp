#pragma once

#include "TArgument.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/SignatureMacro.h"

template <typename Result, typename Index>
struct TSubscriptHelper
{
	template <typename Class>
	static auto Get(BINDING_SUBSCRIPT_GET_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			TReturnValue<Result>(RETURN_BUFFER, std::forward<Result>(
				FoundObject->operator[](TArgument<Index, Index>(IN_BUFFER).Get())));
		}
	}

	template <typename Class>
	static auto Set(BINDING_SUBSCRIPT_SET_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			FoundObject->operator[](TArgument<Index, Index>(IN_BUFFER).Get()) =
				TArgument<Result, Result>(IN_BUFFER + TTypeInfo<std::decay_t<Index>>::Get()->GetBufferSize()).Get();
		}
	}
};
