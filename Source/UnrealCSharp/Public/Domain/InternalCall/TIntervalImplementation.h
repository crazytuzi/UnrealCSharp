#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U>
class TIntervalImplementation
{
public:
	static auto Interval_SizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Interval_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Interval_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const U Element);

	static auto Interval_ExpandImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          const U ExpandAmount);

	static auto Interval_IncludeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const U X);

	static auto Interval_InterpolateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const float Alpha);

	static auto Interval_IntersectImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             MonoObject** OutValue);
};

#include "TIntervalImplementation.inl"
