using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class DateTimeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_AddTimespanImplementation(IntPtr A, IntPtr B, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_AddDateTimeImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_SubtractDateTimeImplementation(IntPtr A, IntPtr B,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_SubtractTimespanImplementation(IntPtr A, IntPtr B,
            out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_GreaterThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_LessThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetDatePartImplementation(IntPtr InDateTime, out FDateTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetDateComponentsImplementation(IntPtr InDateTime, out Int32 OutYear,
            out Int32 OutMonth, out Int32 OutDay);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetDayImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetDayOfYearImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetHourImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetHour12Implementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double DateTime_GetJulianDayImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double DateTime_GetModifiedJulianDayImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMillisecondImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMinuteImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetMonthImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetSecondImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 DateTime_GetTicksImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_GetTimeOfDayImplementation(IntPtr InDateTime, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 DateTime_GetYearImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_IsAfternoonImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean DateTime_IsMorningImplementation(IntPtr InDateTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToHttpDateImplementation(IntPtr InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToIso8601Implementation(IntPtr InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void DateTime_ToStringImplementation(IntPtr InDateTime, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 DateTime_ToUnixTimestampImplementation(IntPtr InDateTime);

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