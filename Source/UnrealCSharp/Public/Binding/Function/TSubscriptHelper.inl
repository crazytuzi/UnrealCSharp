#pragma once

#include "TBufferOffset.inl"
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
				                     FoundObject->operator[](
					                     TArgument<Index, Index>(
						                     IN_BUFFER + std::get<0>(TBufferOffset<Index>()())).Get())));
		}
	}

	template <typename Class>
	static auto Set(BINDING_SUBSCRIPT_SET_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InGarbageCollectionHandle))
		{
			FoundObject->operator[](
					TArgument<Index, Index>(
						IN_BUFFER + std::get<0>(TBufferOffset<Index, Result>()())).Get()) =
				TArgument<Result, Result>(
					IN_BUFFER + std::get<1>(TBufferOffset<Index, Result>()())).Get();
		}
	}
};
