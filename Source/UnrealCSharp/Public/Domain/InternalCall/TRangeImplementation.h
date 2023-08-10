#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U, typename V>
class TRangeImplementation
{
public:
	static auto Range_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static auto Range_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static auto Range_AdjoinsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        const MonoObject* Other);

	static auto Range_ConjoinsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         const MonoObject* X, const MonoObject* Y);

	static auto Range_ContainsElementImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const V Element);

	static auto Range_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         const MonoObject* Other);

	static auto Range_ContiguousImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           const MonoObject* Other);

	static auto Range_GetLowerBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** OutValue);

	static auto Range_SetLowerBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* NewLowerBound);

	static auto Range_SetLowerBoundValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const V NewLowerBoundValue);

	static auto Range_GetLowerBoundValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_GetUpperBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** OutValue);

	static auto Range_SetUpperBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* NewUpperBound);

	static auto Range_SetUpperBoundValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   const V NewUpperBoundValue);

	static auto Range_GetUpperBoundValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_HasLowerBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_HasUpperBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_IsDegenerateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_IsEmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static auto Range_OverlapsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         const MonoObject* Other);

	static auto Range_HullImplementation(const MonoObject* X, const MonoObject* Y, MonoObject** OutValue);

	static auto Range_IntersectionImplementation(const MonoObject* X, const MonoObject* Y, MonoObject** OutValue);

	static auto Range_AllImplementation(MonoObject** OutValue);

	static auto Range_AtLeastImplementation(const V Value, MonoObject** OutValue);

	static auto Range_AtMostImplementation(const V Value, MonoObject** OutValue);

	static auto Range_EmptyImplementation(MonoObject** OutValue);

	static auto Range_ExclusiveImplementation(const V Min, const V Max, MonoObject** OutValue);

	static auto Range_GreaterThanImplementation(const V Value, MonoObject** OutValue);

	static auto Range_InclusiveImplementation(const V Min, const V Max, MonoObject** OutValue);

	static auto Range_LessThanImplementation(const V Value, MonoObject** OutValue);
};

#include "TRangeImplementation.inl"
