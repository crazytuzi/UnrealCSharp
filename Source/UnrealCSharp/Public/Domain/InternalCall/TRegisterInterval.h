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
			.Function("Size",
			          static_cast<void*>(FIntervalImplementation::Interval_SizeImplementation))
			.Function("IsValid",
			          static_cast<void*>(FIntervalImplementation::Interval_IsValidImplementation))
			.Function("Contains",
			          static_cast<void*>(FIntervalImplementation::Interval_ContainsImplementation))
			.Function("Expand",
			          static_cast<void*>(FIntervalImplementation::Interval_ExpandImplementation))
			.Function("Include",
			          static_cast<void*>(FIntervalImplementation::Interval_IncludeImplementation))
			.Function("Interpolate",
			          static_cast<void*>(FIntervalImplementation::Interval_InterpolateImplementation))
			.Function("Intersect",
			          static_cast<void*>(FIntervalImplementation::Interval_IntersectImplementation))
			.Register();
	}
};
