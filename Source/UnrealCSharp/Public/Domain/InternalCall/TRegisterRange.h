#pragma once

#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Domain/InternalCall/TRangeImplementation.h"
#include "Macro/NamespaceMacro.h"

template <typename T, typename U, typename V>
struct TRegisterRange
{
	typedef TRangeImplementation<T, U, V> FRangeImplementation;

	TRegisterRange()
	{
		TReflectionClassBuilder<T>(NAMESPACE_LIBRARY)
			.Function("Adjoins", FRangeImplementation::Range_AdjoinsImplementation)
			.Function("Conjoins", FRangeImplementation::Range_ConjoinsImplementation)
			.Function("ContainsElement", FRangeImplementation::Range_ContainsElementImplementation)
			.Function("Contains", FRangeImplementation::Range_ContainsImplementation)
			.Function("Contiguous", FRangeImplementation::Range_ContiguousImplementation)
			.Function("GetLowerBound", FRangeImplementation::Range_GetLowerBoundImplementation)
			.Function("SetLowerBound", FRangeImplementation::Range_SetLowerBoundImplementation)
			.Function("SetLowerBoundValue", FRangeImplementation::Range_SetLowerBoundValueImplementation)
			.Function("GetLowerBoundValue", FRangeImplementation::Range_GetLowerBoundValueImplementation)
			.Function("GetUpperBound", FRangeImplementation::Range_GetUpperBoundImplementation)
			.Function("SetUpperBound", FRangeImplementation::Range_SetUpperBoundImplementation)
			.Function("SetUpperBoundValue", FRangeImplementation::Range_SetUpperBoundValueImplementation)
			.Function("GetUpperBoundValue", FRangeImplementation::Range_GetUpperBoundValueImplementation)
			.Function("HasLowerBound", FRangeImplementation::Range_HasLowerBoundImplementation)
			.Function("HasUpperBound", FRangeImplementation::Range_HasUpperBoundImplementation)
			.Function("IsDegenerate", FRangeImplementation::Range_IsDegenerateImplementation)
			.Function("IsEmpty", FRangeImplementation::Range_IsEmptyImplementation)
			.Function("Overlaps", FRangeImplementation::Range_OverlapsImplementation)
			.Function("Overlaps", FRangeImplementation::Range_HullImplementation)
			.Function("Intersection", FRangeImplementation::Range_IntersectionImplementation)
			.Function("All", FRangeImplementation::Range_AllImplementation)
			.Function("AtLeast", FRangeImplementation::Range_AtLeastImplementation)
			.Function("AtMost", FRangeImplementation::Range_AtMostImplementation)
			.Function("Empty", FRangeImplementation::Range_EmptyImplementation)
			.Function("Exclusive", FRangeImplementation::Range_ExclusiveImplementation)
			.Function("GreaterThan", FRangeImplementation::Range_GreaterThanImplementation)
			.Function("Inclusive", FRangeImplementation::Range_InclusiveImplementation)
			.Function("LessThan", FRangeImplementation::Range_LessThanImplementation)
			.Register();
	}
};
