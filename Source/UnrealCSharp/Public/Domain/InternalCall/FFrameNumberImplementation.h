#pragma once

#include "mono/metadata/object-forward.h"

class FFrameNumberImplementation
{
public:
	static void FrameNumber_IncrementImplementation(const MonoObject* InMonoObject);

	static void FrameNumber_DecrementImplementation(const MonoObject* InMonoObject);

	static bool FrameNumber_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameNumber_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameNumber_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameNumber_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameNumber_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameNumber_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static void FrameNumber_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameNumber_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameNumber_RemainderImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameNumber_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void FrameNumber_MultiplyImplementation(const MonoObject* InMonoObject, float Scalar, MonoObject** OutValue);

	static void FrameNumber_DivideImplementation(const MonoObject* InMonoObject, float Scalar, MonoObject** OutValue);
};
