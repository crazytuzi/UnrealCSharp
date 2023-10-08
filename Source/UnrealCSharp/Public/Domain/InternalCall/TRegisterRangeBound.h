#pragma once

#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Domain/InternalCall/TRangeBoundImplementation.h"
#include "Macro/NamespaceMacro.h"

template <typename T, typename U>
struct TRegisterRangeBound
{
	typedef TRangeBoundImplementation<T, U> FRangeBoundImplementation;

	TRegisterRangeBound()
	{
		TReflectionClassBuilder<T>(NAMESPACE_LIBRARY)
			.Function("GetValue", FRangeBoundImplementation::RangeBound_GetValueImplementation)
			.Function("SetValue", FRangeBoundImplementation::RangeBound_SetValueImplementation)
			.Function("IsClosed", FRangeBoundImplementation::RangeBound_IsClosedImplementation)
			.Function("IsExclusive", FRangeBoundImplementation::RangeBound_IsExclusiveImplementation)
			.Function("IsInclusive", FRangeBoundImplementation::RangeBound_IsInclusiveImplementation)
			.Function("IsOpen", FRangeBoundImplementation::RangeBound_IsOpenImplementation)
			.Function("Exclusive", FRangeBoundImplementation::RangeBound_ExclusiveImplementation)
			.Function("Inclusive", FRangeBoundImplementation::RangeBound_InclusiveImplementation)
			.Function("Open", FRangeBoundImplementation::RangeBound_OpenImplementation)
			.Function("FlipInclusion", FRangeBoundImplementation::RangeBound_FlipInclusionImplementation)
			.Function("MaxLower", FRangeBoundImplementation::RangeBound_MaxLowerImplementation)
			.Function("MaxUpper", FRangeBoundImplementation::RangeBound_MaxUpperImplementation)
			.Function("MinLower", FRangeBoundImplementation::RangeBound_MinLowerImplementation)
			.Function("MinUpper", FRangeBoundImplementation::RangeBound_MinUpperImplementation)
			.Register();
	}
};
