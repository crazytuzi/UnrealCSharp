#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FTimespanImplementation
{
public:
	static void Timespan_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                       MonoObject** OutValue);

	static void Timespan_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void Timespan_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                            MonoObject** OutValue);

	static void Timespan_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, double Scalar,
	                                            MonoObject** OutValue);

	static void Timespan_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, double Scalar,
	                                          MonoObject** OutValue);

	static void Timespan_RemainderImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                             MonoObject** OutValue);

	static bool Timespan_GreaterThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Timespan_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);

	static bool Timespan_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Timespan_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static int32 Timespan_GetDaysImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Timespan_GetDurationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static int32 Timespan_GetFractionMicroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetFractionMilliImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetFractionNanoImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetFractionTicksImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetHoursImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetMinutesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 Timespan_GetSecondsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int64 Timespan_GetTicksImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalDaysImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalHoursImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalMicrosecondsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalMillisecondsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalMinutesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double Timespan_GetTotalSecondsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Timespan_IsZeroImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Timespan_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static void Timespan_FromDaysImplementation(double Days, MonoObject** OutValue);

	static void Timespan_FromHoursImplementation(double Hours, MonoObject** OutValue);

	static void Timespan_FromMicrosecondsImplementation(double Microseconds, MonoObject** OutValue);

	static void Timespan_FromMillisecondsImplementation(double Milliseconds, MonoObject** OutValue);

	static void Timespan_FromMinutesImplementation(double Minutes, MonoObject** OutValue);

	static void Timespan_FromSecondsImplementation(double Seconds, MonoObject** OutValue);

	static void Timespan_MaxValueImplementation(MonoObject** OutValue);

	static void Timespan_MinValueImplementation(MonoObject** OutValue);

	static bool Timespan_ParseImplementation(MonoObject* TimespanString, MonoObject** OutValue);

	static double Timespan_RatioImplementation(const MonoObject* Dividend, const MonoObject* Divisor);

	static void Timespan_ZeroImplementation(MonoObject** OutValue);
};
