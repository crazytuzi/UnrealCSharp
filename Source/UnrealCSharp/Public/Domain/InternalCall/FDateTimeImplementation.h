#pragma once

#include "mono/metadata/object-forward.h"

class FDateTimeImplementation
{
public:
	static void DateTime_AddTimespanImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void DateTime_AddDateTimeImplementation(const MonoObject* A, const MonoObject* B);

	static void DateTime_SubtractDateTimeImplementation(const MonoObject* A, const MonoObject* B,
	                                                    MonoObject** OutValue);

	static void DateTime_SubtractTimespanImplementation(const MonoObject* A, const MonoObject* B,
	                                                    MonoObject** OutValue);

	static bool DateTime_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool DateTime_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool DateTime_GreaterThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool DateTime_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static bool DateTime_LessThanImplementation(const MonoObject* A, const MonoObject* B);

	static bool DateTime_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B);

	static void DateTime_GetDatePartImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void DateTime_GetDateComponentsImplementation(const MonoObject* InMonoObject, int32& OutYear,
	                                                     int32& OutMonth, int32& OutDay);

	static int32 DateTime_GetDayImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetDayOfYearImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetHourImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetHour12Implementation(const MonoObject* InMonoObject);

	static double DateTime_GetJulianDayImplementation(const MonoObject* InMonoObject);

	static double DateTime_GetModifiedJulianDayImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetMillisecondImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetMinuteImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetMonthImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_GetSecondImplementation(const MonoObject* InMonoObject);

	static int64 DateTime_GetTicksImplementation(const MonoObject* InMonoObject);

	static void DateTime_GetTimeOfDayImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static int32 DateTime_GetYearImplementation(const MonoObject* InMonoObject);

	static bool DateTime_IsAfternoonImplementation(const MonoObject* InMonoObject);

	static bool DateTime_IsMorningImplementation(const MonoObject* InMonoObject);

	static void DateTime_ToHttpDateImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void DateTime_ToIso8601Implementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void DateTime_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static int64 DateTime_ToUnixTimestampImplementation(const MonoObject* InMonoObject);

	static int32 DateTime_DaysInMonthImplementation(int32 Year, int32 Month);

	static int32 DateTime_DaysInYearImplementation(int32 Year);

	static void DateTime_FromJulianDayImplementation(double JulianDay, MonoObject** OutValue);

	static void DateTime_FromUnixTimestampImplementation(int64 UnixTime, MonoObject** OutValue);

	static bool DateTime_IsLeapYearImplementation(int32 Year);

	static void DateTime_MaxValueImplementation(MonoObject** OutValue);

	static void DateTime_MinValueImplementation(MonoObject** OutValue);

	static void DateTime_NowImplementation(MonoObject** OutValue);

	static bool DateTime_ParseImplementation(MonoObject* DateTimeString, MonoObject** OutValue);

	static bool DateTime_ParseHttpDateImplementation(MonoObject* HttpDate, MonoObject** OutValue);

	static void DateTime_TodayImplementation(MonoObject** OutValue);

	static void DateTime_UtcNowImplementation(MonoObject** OutValue);

	static bool DateTime_ValidateImplementation(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute,
	                                            int32 Second, int32 Millisecond);
};
