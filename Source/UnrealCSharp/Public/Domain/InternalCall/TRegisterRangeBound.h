#pragma once

#include "Binding/Class/TScriptStructBuilder.h"
#include "Domain/InternalCall/TRangeBoundImplementation.h"
#include "Macro/NamespaceMacro.h"

template <typename T, typename U>
struct TRegisterRangeBound
{
	typedef TRangeBoundImplementation<T, U> FRangeBoundImplementation;

	TRegisterRangeBound()
	{
		TScriptStructBuilder<T>(NAMESPACE_LIBRARY)
			.Function("Equality",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_EqualityImplementation))
			.Function("Inequality",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_InequalityImplementation))
			.Function("GetValue",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_GetValueImplementation))
			.Function("SetValue",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_SetValueImplementation))
			.Function("IsClosed",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_IsClosedImplementation))
			.Function("IsExclusive",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_IsExclusiveImplementation))
			.Function("IsInclusive",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_IsInclusiveImplementation))
			.Function("IsOpen",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_IsOpenImplementation))
			.Function("Exclusive",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_ExclusiveImplementation))
			.Function("Inclusive",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_InclusiveImplementation))
			.Function("Open",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_OpenImplementation))
			.Function("FlipInclusion",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_FlipInclusionImplementation))
			.Function("MaxLower",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_MaxLowerImplementation))
			.Function("MaxUpper",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_MaxUpperImplementation))
			.Function("MinLower",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_MinLowerImplementation))
			.Function("MinUpper",
			          static_cast<void*>(FRangeBoundImplementation::RangeBound_MinUpperImplementation))
			.Register();
	}
};
