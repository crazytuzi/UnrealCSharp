#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U>
class TIntervalImplementation
{
public:
	static auto Interval_SizeImplementation(const MonoObject* InMonoObject);

	static auto Interval_IsValidImplementation(const MonoObject* InMonoObject);

	static auto Interval_ContainsImplementation(const MonoObject* InMonoObject, const U Element);

	static auto Interval_ExpandImplementation(const MonoObject* InMonoObject, const U ExpandAmount);

	static auto Interval_IncludeImplementation(const MonoObject* InMonoObject, const U X);

	static auto Interval_InterpolateImplementation(const MonoObject* InMonoObject, const float Alpha);

	static auto Interval_IntersectImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);
};

#include "TIntervalImplementation.inl"
