#pragma once

#include "TArgument.inl"
#include "Environment/FCSharpEnvironment.h"

extern MonoObject* Get(MonoArray* InMonoArray, const size_t InIndex);

template <typename>
struct TDestructorHelper
{
};

template <typename... Args>
struct TDestructorHelper<std::tuple<Args...>>
{
	template <size_t... Index>
	static void Call(std::index_sequence<Index...>, BINDING_DESTRUCTOR_SIGNATURE)
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference(InGarbageCollectionHandle);
	}
};
