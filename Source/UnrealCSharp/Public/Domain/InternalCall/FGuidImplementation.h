#pragma once

#include "mono/metadata/object-forward.h"

class FGuidImplementation
{
public:
	static bool Guid_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Guid_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Guid_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool Guid_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static uint32 Guid_GetComponentImplementation(const MonoObject* InMonoObject, int32 Index);

	static void Guid_SetComponentImplementation(const MonoObject* InMonoObject, int32 Index, uint32 InValue);

	static void Guid_LexToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Guid_InvalidateImplementation(const MonoObject* InMonoObject);

	static bool Guid_IsValidImplementation(const MonoObject* InMonoObject);

	static void Guid_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Guid_NewGuidImplementation(MonoObject** OutValue);

	static bool Guid_ParseImplementation(MonoObject* GuidString, MonoObject** OutGuid);
};
