#pragma once

#include "mono/metadata/object-forward.h"

template <typename T, typename U>
class TRangeBoundImplementation
{
public:
	static auto RangeBound_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static auto RangeBound_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static U RangeBound_GetValueImplementation(const MonoObject* InMonoObject);

	static auto RangeBound_SetValueImplementation(const MonoObject* InMonoObject, const U NewValue);

	static auto RangeBound_IsClosedImplementation(const MonoObject* InMonoObject);

	static auto RangeBound_IsExclusiveImplementation(const MonoObject* InMonoObject);

	static auto RangeBound_IsInclusiveImplementation(const MonoObject* InMonoObject);

	static auto RangeBound_IsOpenImplementation(const MonoObject* InMonoObject);

	static auto RangeBound_ExclusiveImplementation(const U Value, MonoObject** OutValue);

	static auto RangeBound_InclusiveImplementation(const U Value, MonoObject** OutValue);

	static auto RangeBound_OpenImplementation(MonoObject** OutValue);

	static auto RangeBound_FlipInclusionImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static auto RangeBound_MaxLowerImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static auto RangeBound_MaxUpperImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static auto RangeBound_MinLowerImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static auto RangeBound_MinUpperImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);
};

#include "TRangeBoundImplementation.inl"
