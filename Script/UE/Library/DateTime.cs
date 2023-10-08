using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FDateTime
    {
        public static FDateTime operator +(FDateTime A, FTimespan B)
        {
            DateTimeImplementation.DateTime_AddTimespanImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FDateTime operator +(FDateTime A, FDateTime B)
        {
            DateTimeImplementation.DateTime_AddDateTimeImplementation(A.GetHandle(), B.GetHandle());

            return A;
        }

        public static FTimespan operator -(FDateTime A, FDateTime B)
        {
            DateTimeImplementation.DateTime_SubtractDateTimeImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FDateTime operator -(FDateTime A, FTimespan B)
        {
            DateTimeImplementation.DateTime_SubtractTimespanImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static Boolean operator >(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >=(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_GreaterThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <=(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_LessThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        // @TODO
        // ExportTextItem

        public FDateTime GetDate()
        {
            DateTimeImplementation.DateTime_GetDatePartImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void GetDate(out Int32 OutYear, out Int32 OutMonth, out Int32 OutDay) =>
            DateTimeImplementation.DateTime_GetDateComponentsImplementation(GetHandle(), out OutYear, out OutMonth,
                out OutDay);

        public Int32 GetDay() =>
            DateTimeImplementation.DateTime_GetDayImplementation(GetHandle());

        // @TODO
        // GetDayOfWeek

        public Int32 GetDayOfYear() =>
            DateTimeImplementation.DateTime_GetDayOfYearImplementation(GetHandle());

        public Int32 GetHour() =>
            DateTimeImplementation.DateTime_GetHourImplementation(GetHandle());

        public Int32 GetHour12() =>
            DateTimeImplementation.DateTime_GetHour12Implementation(GetHandle());

        public Double GetJulianDay() =>
            DateTimeImplementation.DateTime_GetJulianDayImplementation(GetHandle());

        public Double GetModifiedJulianDay() =>
            DateTimeImplementation.DateTime_GetModifiedJulianDayImplementation(GetHandle());

        public Int32 GetMillisecond() =>
            DateTimeImplementation.DateTime_GetMillisecondImplementation(GetHandle());

        public Int32 GetMinute() =>
            DateTimeImplementation.DateTime_GetMinuteImplementation(GetHandle());

        public Int32 GetMonth() =>
            DateTimeImplementation.DateTime_GetMonthImplementation(GetHandle());

        // @TODO
        // GetMonthOfYear

        public Int32 GetSecond() =>
            DateTimeImplementation.DateTime_GetSecondImplementation(GetHandle());

        public Int64 GetTicks() =>
            DateTimeImplementation.DateTime_GetTicksImplementation(GetHandle());

        public FTimespan GetTimeOfDay()
        {
            DateTimeImplementation.DateTime_GetTimeOfDayImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Int32 GetYear() =>
            DateTimeImplementation.DateTime_GetYearImplementation(GetHandle());

        // @TODO
        // ImportTextItem

        public Boolean IsAfternoon() =>
            DateTimeImplementation.DateTime_IsAfternoonImplementation(GetHandle());

        public Boolean IsMorning() =>
            DateTimeImplementation.DateTime_IsMorningImplementation(GetHandle());

        public FString ToHttpDate()
        {
            DateTimeImplementation.DateTime_ToHttpDateImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString ToIso8601()
        {
            DateTimeImplementation.DateTime_ToIso8601Implementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            DateTimeImplementation.DateTime_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        // @TODO
        // ToString

        public Int64 ToUnixTimestamp() =>
            DateTimeImplementation.DateTime_ToUnixTimestampImplementation(GetHandle());

        public static Int32 DaysInMonth(Int32 Year, Int32 Month) =>
            DateTimeImplementation.DateTime_DaysInMonthImplementation(Year, Month);

        public static Int32 DaysInYear(Int32 Year) =>
            DateTimeImplementation.DateTime_DaysInYearImplementation(Year);

        public static FDateTime FromJulianDay(Double JulianDay)
        {
            DateTimeImplementation.DateTime_FromJulianDayImplementation(JulianDay, out var OutValue);

            return OutValue;
        }

        public static FDateTime FromUnixTimestamp(Int64 UnixTime)
        {
            DateTimeImplementation.DateTime_FromUnixTimestampImplementation(UnixTime, out var OutValue);

            return OutValue;
        }

        public static Boolean IsLeapYear(Int32 Year) =>
            DateTimeImplementation.DateTime_IsLeapYearImplementation(Year);

        public static FDateTime MaxValue()
        {
            DateTimeImplementation.DateTime_MaxValueImplementation(out var OutValue);

            return OutValue;
        }

        public static FDateTime MinValue()
        {
            DateTimeImplementation.DateTime_MinValueImplementation(out var OutValue);

            return OutValue;
        }

        public static FDateTime Now()
        {
            DateTimeImplementation.DateTime_NowImplementation(out var OutValue);

            return OutValue;
        }

        public static Boolean Parse(FString DateTimeString, out FDateTime OutDateTime) =>
            DateTimeImplementation.DateTime_ParseImplementation(DateTimeString, out OutDateTime);

        public static Boolean ParseHttpDate(FString HttpDate, out FDateTime OutDateTime) =>
            DateTimeImplementation.DateTime_ParseHttpDateImplementation(HttpDate, out OutDateTime);

        // @TODO
        // ParseIso8601

        public static FDateTime Today()
        {
            DateTimeImplementation.DateTime_TodayImplementation(out var OutValue);

            return OutValue;
        }

        public static FDateTime UtcNow()
        {
            DateTimeImplementation.DateTime_UtcNowImplementation(out var OutValue);

            return OutValue;
        }

        public static Boolean Validate(Int32 Year, Int32 Month, Int32 Day, Int32 Hour, Int32 Minute, Int32 Second,
            Int32 Millisecond) =>
            DateTimeImplementation.DateTime_ValidateImplementation(Year, Month, Day, Hour, Minute, Second, Millisecond);
    }
}