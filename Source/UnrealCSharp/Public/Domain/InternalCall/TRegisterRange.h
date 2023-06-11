#pragma once

#include "Binding/Class/TScriptStructBuilder.inl"
#include "Domain/InternalCall/TRangeImplementation.h"
#include "Macro/NamespaceMacro.h"

template <typename T, typename U, typename V>
struct TRegisterRange
{
	typedef TRangeImplementation<T, U, V> FRangeImplementation;

	TRegisterRange()
	{
		TScriptStructBuilder<T>(NAMESPACE_LIBRARY)
			.Function("Equality",
			          static_cast<void*>(FRangeImplementation::Range_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FRangeImplementation::Range_InequalityImplementation))
			.Function("Adjoins",
			          static_cast<void*>(FRangeImplementation::Range_AdjoinsImplementation))
			.Function("Conjoins",
			          static_cast<void*>(FRangeImplementation::Range_ConjoinsImplementation))
			.Function("ContainsElement",
			          static_cast<void*>(FRangeImplementation::Range_ContainsElementImplementation))
			.Function("Contains",
			          static_cast<void*>(FRangeImplementation::Range_ContainsImplementation))
			.Function("Contiguous",
			          static_cast<void*>(FRangeImplementation::Range_ContiguousImplementation))
			.Function("GetLowerBound",
			          static_cast<void*>(FRangeImplementation::Range_GetLowerBoundImplementation))
			.Function("SetLowerBound",
			          static_cast<void*>(FRangeImplementation::Range_SetLowerBoundImplementation))
			.Function("SetLowerBoundValue",
			          static_cast<void*>(FRangeImplementation::Range_SetLowerBoundValueImplementation))
			.Function("GetLowerBoundValue",
			          static_cast<void*>(FRangeImplementation::Range_GetLowerBoundValueImplementation))
			.Function("GetUpperBound",
			          static_cast<void*>(FRangeImplementation::Range_GetUpperBoundImplementation))
			.Function("SetUpperBound",
			          static_cast<void*>(FRangeImplementation::Range_SetUpperBoundImplementation))
			.Function("SetUpperBoundValue",
			          static_cast<void*>(FRangeImplementation::Range_SetUpperBoundValueImplementation))
			.Function("GetUpperBoundValue",
			          static_cast<void*>(FRangeImplementation::Range_GetUpperBoundValueImplementation))
			.Function("HasLowerBound",
			          static_cast<void*>(FRangeImplementation::Range_HasLowerBoundImplementation))
			.Function("HasUpperBound",
			          static_cast<void*>(FRangeImplementation::Range_HasUpperBoundImplementation))
			.Function("IsDegenerate",
			          static_cast<void*>(FRangeImplementation::Range_IsDegenerateImplementation))
			.Function("IsEmpty",
			          static_cast<void*>(FRangeImplementation::Range_IsEmptyImplementation))
			.Function("Overlaps",
			          static_cast<void*>(FRangeImplementation::Range_OverlapsImplementation))
			.Function("Overlaps",
			          static_cast<void*>(FRangeImplementation::Range_HullImplementation))
			.Function("Intersection",
			          static_cast<void*>(FRangeImplementation::Range_IntersectionImplementation))
			.Function("All",
			          static_cast<void*>(FRangeImplementation::Range_AllImplementation))
			.Function("AtLeast",
			          static_cast<void*>(FRangeImplementation::Range_AtLeastImplementation))
			.Function("AtMost",
			          static_cast<void*>(FRangeImplementation::Range_AtMostImplementation))
			.Function("Empty",
			          static_cast<void*>(FRangeImplementation::Range_EmptyImplementation))
			.Function("Exclusive",
			          static_cast<void*>(FRangeImplementation::Range_ExclusiveImplementation))
			.Function("GreaterThan",
			          static_cast<void*>(FRangeImplementation::Range_GreaterThanImplementation))
			.Function("Inclusive",
			          static_cast<void*>(FRangeImplementation::Range_InclusiveImplementation))
			.Function("LessThan",
			          static_cast<void*>(FRangeImplementation::Range_LessThanImplementation))
			.Register();
	}
};
