#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U, typename V>
class TRangeImplementation
{
public:
	static auto Range_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static auto Range_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static auto Range_AdjoinsImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static auto Range_ConjoinsImplementation(const MonoObject* InMonoObject, const MonoObject* X, const MonoObject* Y);

	static auto Range_ContainsElementImplementation(const MonoObject* InMonoObject, const V Element);

	static auto Range_ContainsImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static auto Range_ContiguousImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static auto Range_GetLowerBoundImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static auto Range_SetLowerBoundImplementation(const MonoObject* InMonoObject, const MonoObject* NewLowerBound);

	static auto Range_SetLowerBoundValueImplementation(const MonoObject* InMonoObject, const V NewLowerBoundValue);

	static auto Range_GetLowerBoundValueImplementation(const MonoObject* InMonoObject);

	static auto Range_GetUpperBoundImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static auto Range_SetUpperBoundImplementation(const MonoObject* InMonoObject, const MonoObject* NewUpperBound);

	static auto Range_SetUpperBoundValueImplementation(const MonoObject* InMonoObject, const V NewUpperBoundValue);

	static auto Range_GetUpperBoundValueImplementation(const MonoObject* InMonoObject);

	static auto Range_HasLowerBoundImplementation(const MonoObject* InMonoObject);

	static auto Range_HasUpperBoundImplementation(const MonoObject* InMonoObject);

	static auto Range_IsDegenerateImplementation(const MonoObject* InMonoObject);

	static auto Range_IsEmptyImplementation(const MonoObject* InMonoObject);

	static auto Range_OverlapsImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

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
