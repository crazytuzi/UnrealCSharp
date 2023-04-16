using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FTimespan
    {
        public static FTimespan operator +(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator -(FTimespan A)
        {
            TimespanImplementation.Timespan_NegatedImplementation(A, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator -(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator *(FTimespan A, Double Scalar)
        {
            TimespanImplementation.Timespan_MultiplyImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator /(FTimespan A, Double Scalar)
        {
            TimespanImplementation.Timespan_DivideImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator %(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_RemainderImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_EqualityImplementation(A, B);

        public static Boolean operator !=(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_InequalityImplementation(A, B);

        public static Boolean operator >(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_GreaterThanImplementation(A, B);

        public static Boolean operator >=(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_GreaterThanOrEqualImplementation(A, B);

        public static Boolean operator <(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_LessThanImplementation(A, B);

        public static Boolean operator <=(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_LessThanOrEqualImplementation(A, B);

        // @TODO
        // ExportTextItem

        public Int32 GetDays() =>
            TimespanImplementation.Timespan_GetDaysImplementation(this);

        public FTimespan GetDuration()
        {
            TimespanImplementation.Timespan_GetDurationImplementation(this, out var OutValue);

            return OutValue;
        }

        public Int32 GetFractionMicro() =>
            TimespanImplementation.Timespan_GetFractionMicroImplementation(this);

        public Int32 GetFractionMilli() =>
            TimespanImplementation.Timespan_GetFractionMilliImplementation(this);

        public Int32 GetFractionNano() =>
            TimespanImplementation.Timespan_GetFractionNanoImplementation(this);

        public Int32 GetFractionTicks() =>
            TimespanImplementation.Timespan_GetFractionTicksImplementation(this);

        public Int32 GetHours() =>
            TimespanImplementation.Timespan_GetHoursImplementation(this);

        public Int32 GetMinutes() =>
            TimespanImplementation.Timespan_GetMinutesImplementation(this);

        public Int32 GetSeconds() =>
            TimespanImplementation.Timespan_GetSecondsImplementation(this);

        public Int64 GetTicks() =>
            TimespanImplementation.Timespan_GetTicksImplementation(this);

        public Double GetTotalDays() =>
            TimespanImplementation.Timespan_GetTotalDaysImplementation(this);

        public Double GetTotalHours() =>
            TimespanImplementation.Timespan_GetTotalHoursImplementation(this);

        public Double GetTotalMicroseconds() =>
            TimespanImplementation.Timespan_GetTotalMicrosecondsImplementation(this);

        public Double GetTotalMilliseconds() =>
            TimespanImplementation.Timespan_GetTotalMillisecondsImplementation(this);

        public Double GetTotalMinutes() =>
            TimespanImplementation.Timespan_GetTotalMinutesImplementation(this);

        public Double GetTotalSeconds() =>
            TimespanImplementation.Timespan_GetTotalSecondsImplementation(this);

        // @TODO
        // ImportTextItem

        public Boolean IsZero() =>
            TimespanImplementation.Timespan_IsZeroImplementation(this);

        public override string ToString()
        {
            TimespanImplementation.Timespan_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        // @TODO
        // ToString

        public static FTimespan FromDays(Double Days)
        {
            TimespanImplementation.Timespan_FromDaysImplementation(Days, out var OutValue);

            return OutValue;
        }

        public static FTimespan FromHours(Double Hours)
        {
            TimespanImplementation.Timespan_FromHoursImplementation(Hours, out var OutValue);

            return OutValue;
        }

        public static FTimespan FromMicroseconds(Double Microseconds)
        {
            TimespanImplementation.Timespan_FromMicrosecondsImplementation(Microseconds, out var OutValue);

            return OutValue;
        }

        public static FTimespan FromMilliseconds(Double Milliseconds)
        {
            TimespanImplementation.Timespan_FromMillisecondsImplementation(Milliseconds, out var OutValue);

            return OutValue;
        }

        public static FTimespan FromMinutes(Double Minutes)
        {
            TimespanImplementation.Timespan_FromMinutesImplementation(Minutes, out var OutValue);

            return OutValue;
        }

        public static FTimespan FromSeconds(Double Seconds)
        {
            TimespanImplementation.Timespan_FromSecondsImplementation(Seconds, out var OutValue);

            return OutValue;
        }

        public static FTimespan MaxValue()
        {
            TimespanImplementation.Timespan_MaxValueImplementation(out var OutValue);

            return OutValue;
        }

        public static FTimespan MinValue()
        {
            TimespanImplementation.Timespan_MinValueImplementation(out var OutValue);

            return OutValue;
        }

        public static Boolean Parse(FString TimespanString, out FTimespan OutTimespan) =>
            TimespanImplementation.Timespan_ParseImplementation(TimespanString, out OutTimespan);

        public static Double Ratio(FTimespan Dividend, FTimespan Divisor) =>
            TimespanImplementation.Timespan_RatioImplementation(Dividend, Divisor);

        public static FTimespan Zero()
        {
            TimespanImplementation.Timespan_ZeroImplementation(out var OutValue);

            return OutValue;
        }
    }
}