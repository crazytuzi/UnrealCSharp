#pragma once

#include "TArgument.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/SignatureMacro.h"

extern MonoObject* Get(MonoArray* InMonoArray, const size_t InIndex);

template <typename>
struct TDestructorHelper
{
};

template <typename... Args>
struct TDestructorHelper<std::tuple<Args...>>
{
	template <auto... Index>
	static auto Call(std::index_sequence<Index...>, BINDING_DESTRUCTOR_SIGNATURE)
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference(InGarbageCollectionHandle);
	}
};
