#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FFrameNumberImplementation
{
public:
	static void FrameNumber_IncrementImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void FrameNumber_DecrementImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool FrameNumber_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameNumber_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                 const FGarbageCollectionHandle B);

	static bool FrameNumber_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool FrameNumber_GreaterThanImplementation(const FGarbageCollectionHandle A,
	                                                  const FGarbageCollectionHandle B);

	static bool FrameNumber_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);

	static bool FrameNumber_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                         const FGarbageCollectionHandle B);

	static void FrameNumber_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                          MonoObject** OutValue);

	static void FrameNumber_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                               MonoObject** OutValue);

	static void FrameNumber_RemainderImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                                MonoObject** OutValue);

	static void FrameNumber_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** OutValue);

	static void FrameNumber_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               float Scalar, MonoObject** OutValue);

	static void FrameNumber_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, float Scalar,
	                                             MonoObject** OutValue);
};
