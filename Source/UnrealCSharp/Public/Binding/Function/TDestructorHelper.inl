#pragma once

#include "TArgument.inl"
#include "Environment/FCSharpEnvironment.h"

extern MonoObject* Get(MonoArray* InMonoArray, const SIZE_T InIndex);

template <typename>
struct TDestructorHelper
{
};

template <typename... Args>
struct TDestructorHelper<TTuple<Args...>>
{
	template <typename Class, SIZE_T... Index>
	static void Call(TIntegerSequence<SIZE_T, Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference<Class>(InGarbageCollectionHandle);
	}
};
