using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class DateTimeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_AddTimespanImplementation(FDateTime A, FTimespan B, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_AddDateTimeImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_SubtractDateTimeImplementation(FDateTime A, FDateTime B,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_SubtractTimespanImplementation(FDateTime A, FTimespan B,
            out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_EqualityImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_InequalityImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_GreaterThanImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_GreaterThanOrEqualImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_LessThanImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_LessThanOrEqualImplementation(FDateTime A, FDateTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetDatePartImplementation(FDateTime InDateTime, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetDateComponentsImplementation(FDateTime InDateTime, out Int32 OutYear,
            out Int32 OutMonth, out Int32 OutDay);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetDayImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetDayOfYearImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetHourImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetHour12Implementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double DateTime_GetJulianDayImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double DateTime_GetModifiedJulianDayImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMillisecondImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMinuteImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMonthImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetSecondImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 DateTime_GetTicksImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetTimeOfDayImplementation(FDateTime InDateTime, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetYearImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_IsAfternoonImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_IsMorningImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToHttpDateImplementation(FDateTime InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToIso8601Implementation(FDateTime InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToStringImplementation(FDateTime InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 DateTime_ToUnixTimestampImplementation(FDateTime InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_DaysInMonthImplementation(Int32 Year, Int32 Month);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_DaysInYearImplementation(Int32 Year);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_FromJulianDayImplementation(Double JulianDay, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_FromUnixTimestampImplementation(Int64 UnixTime, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_IsLeapYearImplementation(Int32 Year);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_MaxValueImplementation(out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_MinValueImplementation(out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_NowImplementation(out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_ParseImplementation(FString DateTimeString, out FDateTime OutDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_ParseHttpDateImplementation(FString HttpDate, out FDateTime OutDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_TodayImplementation(out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_UtcNowImplementation(out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_ValidateImplementation(Int32 Year, Int32 Month, Int32 Day, Int32 Hour,
            Int32 Minute, Int32 Second, Int32 Millisecond);
    }
}