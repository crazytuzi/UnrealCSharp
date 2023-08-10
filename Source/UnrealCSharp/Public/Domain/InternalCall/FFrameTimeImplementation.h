#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FFrameTimeImplementation
{
public:
	static void FrameTime_GetFrameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static float FrameTime_GetSubFrameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void FrameTime_FloorToFrameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static void FrameTime_CeilToFrameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static void FrameTime_RoundToFrameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 MonoObject** OutValue);

	static double FrameTime_AsDecimalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void FrameTime_FromDecimalImplementation(double InDecimalFrame, MonoObject** OutValue);

	static bool FrameTime_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameTime_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameTime_GreaterThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameTime_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                       const FGarbageCollectionHandle B);

	static bool FrameTime_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameTime_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B);

	static void FrameTime_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        MonoObject** OutValue);

	static void FrameTime_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             MonoObject** OutValue);

	static void FrameTime_RemainderImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                              MonoObject** OutValue);

	static void FrameTime_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void FrameTime_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, float Scalar,
	                                             MonoObject** OutValue);

	static void FrameTime_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, float Scalar,
	                                           MonoObject** OutValue);
};
