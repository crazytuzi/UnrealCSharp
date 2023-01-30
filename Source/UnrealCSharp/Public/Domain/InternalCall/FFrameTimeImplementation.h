#pragma once

#include "mono/metadata/object-forward.h"

class FFrameTimeImplementation
{
public:
	static void FrameTime_GetFrameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static float FrameTime_GetSubFrameImplementation(const MonoObject* InMonoObject);

	static void FrameTime_FloorToFrameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void FrameTime_CeilToFrameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void FrameTime_RoundToFrameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static double FrameTime_AsDecimalImplementation(const MonoObject* InMonoObject);

	static void FrameTime_FromDecimalImplementation(double InDecimalFrame, MonoObject** OutValue);

	static bool FrameTime_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameTime_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameTime_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameTime_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameTime_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool FrameTime_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static void FrameTime_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameTime_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameTime_RemainderImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void FrameTime_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void FrameTime_MultiplyImplementation(const MonoObject* InMonoObject, float Scalar, MonoObject** OutValue);

	static void FrameTime_DivideImplementation(const MonoObject* InMonoObject, float Scalar, MonoObject** OutValue);
};
