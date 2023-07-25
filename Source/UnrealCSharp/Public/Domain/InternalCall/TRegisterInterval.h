#pragma once

#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Domain/InternalCall/TIntervalImplementation.h"
#include "Macro/NamespaceMacro.h"

template <typename T, typename U>
struct TRegisterInterval
{
	typedef TIntervalImplementation<T, U> FIntervalImplementation;

	TRegisterInterval()
	{
		TReflectionClassBuilder<T>(NAMESPACE_LIBRARY)
			.Function("Size", FIntervalImplementation::Interval_SizeImplementation)
			.Function("IsValid", FIntervalImplementation::Interval_IsValidImplementation)
			.Function("Contains", FIntervalImplementation::Interval_ContainsImplementation)
			.Function("Expand", FIntervalImplementation::Interval_ExpandImplementation)
			.Function("Include", FIntervalImplementation::Interval_IncludeImplementation)
			.Function("Interpolate", FIntervalImplementation::Interval_InterpolateImplementation)
			.Function("Intersect", FIntervalImplementation::Interval_IntersectImplementation)
			.Register();
	}
};
