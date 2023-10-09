#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FDateTimeImplementation
{
public:
	static void DateTime_AddTimespanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                               MonoObject** OutValue);

	static void DateTime_AddDateTimeImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void DateTime_SubtractDateTimeImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B, MonoObject** OutValue);

	static void DateTime_SubtractTimespanImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B, MonoObject** OutValue);

	static bool DateTime_GreaterThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool DateTime_GreaterThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                      const FGarbageCollectionHandle B);

	static bool DateTime_LessThanImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool DateTime_LessThanOrEqualImplementation(const FGarbageCollectionHandle A,
	                                                   const FGarbageCollectionHandle B);

	static void DateTime_GetDatePartImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static void DateTime_GetDateComponentsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     int32& OutYear, int32& OutMonth, int32& OutDay);

	static int32 DateTime_GetDayImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetDayOfYearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetHourImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetHour12Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double DateTime_GetJulianDayImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static double DateTime_GetModifiedJulianDayImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetMillisecondImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetMinuteImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetMonthImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 DateTime_GetSecondImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int64 DateTime_GetTicksImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void DateTime_GetTimeOfDayImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static int32 DateTime_GetYearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool DateTime_IsAfternoonImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool DateTime_IsMorningImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void DateTime_ToHttpDateImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** OutValue);

	static void DateTime_ToIso8601Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             MonoObject** OutValue);

	static void DateTime_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            MonoObject** OutValue);

	static int64 DateTime_ToUnixTimestampImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

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
