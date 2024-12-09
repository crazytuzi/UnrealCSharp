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
			auto Value = TReturnValue<Result>(std::forward<Result>(
				FoundObject->operator[](TArgument<Index, Index>(IN_BUFFER).Get())
			)).Get();

			if constexpr (TIsPrimitive<Result>::Value)
			{
				*(std::remove_const_t<std::decay_t<Result>>*)RETURN_BUFFER = Value;
			}
			else
			{
				*reinterpret_cast<void**>(RETURN_BUFFER) = Value;
			}
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
