#pragma once

#include "mono/metadata/object-forward.h"

class FTimespanImplementation
{
public:
	static void Timespan_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Timespan_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Timespan_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Timespan_MultiplyImplementation(const MonoObject* InMonoObject, double Scalar, MonoObject** OutValue);

	static void Timespan_DivideImplementation(const MonoObject* InMonoObject, double Scalar, MonoObject** OutValue);

	static void Timespan_RemainderImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static bool Timespan_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Timespan_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Timespan_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool Timespan_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static bool Timespan_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool Timespan_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static int32 Timespan_GetDaysImplementation(const MonoObject* InMonoObject);

	static void Timespan_GetDurationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static int32 Timespan_GetFractionMicroImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetFractionMilliImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetFractionNanoImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetFractionTicksImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetHoursImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetMinutesImplementation(const MonoObject* InMonoObject);

	static int32 Timespan_GetSecondsImplementation(const MonoObject* InMonoObject);

	static int64 Timespan_GetTicksImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalDaysImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalHoursImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalMicrosecondsImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalMillisecondsImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalMinutesImplementation(const MonoObject* InMonoObject);

	static double Timespan_GetTotalSecondsImplementation(const MonoObject* InMonoObject);

	static bool Timespan_IsZeroImplementation(const MonoObject* InMonoObject);

	static void Timespan_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

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
