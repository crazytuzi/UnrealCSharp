#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U>
class TRangeBoundImplementation
{
public:
	static auto RangeBound_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static auto RangeBound_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static U RangeBound_GetValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto RangeBound_SetValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const U NewValue);

	static auto RangeBound_IsClosedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto RangeBound_IsExclusiveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto RangeBound_IsInclusiveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto RangeBound_IsOpenImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto RangeBound_ExclusiveImplementation(const U Value, MonoObject** OutValue);

	static auto RangeBound_InclusiveImplementation(const U Value, MonoObject** OutValue);

	static auto RangeBound_OpenImplementation(MonoObject** OutValue);

	static auto RangeBound_FlipInclusionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);

	static auto RangeBound_MaxLowerImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static auto RangeBound_MaxUpperImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static auto RangeBound_MinLowerImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static auto RangeBound_MinUpperImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);
};

#include "TRangeBoundImplementation.inl"
