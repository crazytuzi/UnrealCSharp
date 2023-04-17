using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FDateTime
    {
        public static FDateTime operator +(FDateTime A, FTimespan B)
        {
            DateTimeImplementation.DateTime_AddTimespanImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FDateTime operator +(FDateTime A, FDateTime B)
        {
            DateTimeImplementation.DateTime_AddDateTimeImplementation(A, B);

            return A;
        }

        public static FTimespan operator -(FDateTime A, FDateTime B)
        {
            DateTimeImplementation.DateTime_SubtractDateTimeImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FDateTime operator -(FDateTime A, FTimespan B)
        {
            DateTimeImplementation.DateTime_SubtractTimespanImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_EqualityImplementation(A, B);

        public static Boolean operator !=(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_InequalityImplementation(A, B);

        public static Boolean operator >(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_GreaterThanImplementation(A, B);

        public static Boolean operator >=(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_GreaterThanOrEqualImplementation(A, B);

        public static Boolean operator <(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_LessThanImplementation(A, B);

        public static Boolean operator <=(FDateTime A, FDateTime B) =>
            DateTimeImplementation.DateTime_LessThanOrEqualImplementation(A, B);

        // @TODO
        // ExportTextItem

        public FDateTime GetDate()
        {
            DateTimeImplementation.DateTime_GetDatePartImplementation(this, out var OutValue);

            return OutValue;
        }

        public void GetDate(out Int32 OutYear, out Int32 OutMonth, out Int32 OutDay) =>
            DateTimeImplementation.DateTime_GetDateComponentsImplementation(this, out OutYear, out OutMonth,
                out OutDay);

        public Int32 GetDay() =>
            DateTimeImplementation.DateTime_GetDayImplementation(this);

        // @TODO
        // GetDayOfWeek

        public Int32 GetDayOfYear() =>
            DateTimeImplementation.DateTime_GetDayOfYearImplementation(this);

        public Int32 GetHour() =>
            DateTimeImplementation.DateTime_GetHourImplementation(this);

        public Int32 GetHour12() =>
            DateTimeImplementation.DateTime_GetHour12Implementation(this);

        public Double GetJulianDay() =>
            DateTimeImplementation.DateTime_GetJulianDayImplementation(this);

        public Double GetModifiedJulianDay() =>
            DateTimeImplementation.DateTime_GetModifiedJulianDayImplementation(this);

        public Int32 GetMillisecond() =>
            DateTimeImplementation.DateTime_GetMillisecondImplementation(this);

        public Int32 GetMinute() =>
            DateTimeImplementation.DateTime_GetMinuteImplementation(this);

        public Int32 GetMonth() =>
            DateTimeImplementation.DateTime_GetMonthImplementation(this);

        // @TODO
        // GetMonthOfYear

        public Int32 GetSecond() =>
            DateTimeImplementation.DateTime_GetSecondImplementation(this);

        public Int64 GetTicks() =>
            DateTimeImplementation.DateTime_GetTicksImplementation(this);

        public FTimespan GetTimeOfDay()
        {
            DateTimeImplementation.DateTime_GetTimeOfDayImplementation(this, out var OutValue);

            return OutValue;
        }

        public Int32 GetYear() =>
            DateTimeImplementation.DateTime_GetYearImplementation(this);

        // @TODO
        // ImportTextItem

        public Boolean IsAfternoon() =>
            DateTimeImplementation.DateTime_IsAfternoonImplementation(this);

        public Boolean IsMorning() =>
            DateTimeImplementation.DateTime_IsMorningImplementation(this);

        public FString ToHttpDate()
        {
            DateTimeImplementation.DateTime_ToHttpDateImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ToIso8601()
        {
            DateTimeImplementation.DateTime_ToIso8601Implementation(this, out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            DateTimeImplementation.DateTime_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        // @TODO
        // ToString

        public Int64 ToUnixTimestamp() =>
            DateTimeImplementation.DateTime_ToUnixTimestampImplementation(this);

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