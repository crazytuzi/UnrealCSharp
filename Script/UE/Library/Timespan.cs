using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FTimespan
    {
        public static FTimespan operator +(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FTimespan operator -(FTimespan A)
        {
            TimespanImplementation.Timespan_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FTimespan operator -(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FTimespan operator *(FTimespan A, Double Scalar)
        {
            TimespanImplementation.Timespan_MultiplyImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator /(FTimespan A, Double Scalar)
        {
            TimespanImplementation.Timespan_DivideImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }

        public static FTimespan operator %(FTimespan A, FTimespan B)
        {
            TimespanImplementation.Timespan_RemainderImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static Boolean operator >(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >=(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_GreaterThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <=(FTimespan A, FTimespan B) =>
            TimespanImplementation.Timespan_LessThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        // @TODO
        // ExportTextItem

        public Int32 GetDays() =>
            TimespanImplementation.Timespan_GetDaysImplementation(GetHandle());

        public FTimespan GetDuration()
        {
            TimespanImplementation.Timespan_GetDurationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Int32 GetFractionMicro() =>
            TimespanImplementation.Timespan_GetFractionMicroImplementation(GetHandle());

        public Int32 GetFractionMilli() =>
            TimespanImplementation.Timespan_GetFractionMilliImplementation(GetHandle());

        public Int32 GetFractionNano() =>
            TimespanImplementation.Timespan_GetFractionNanoImplementation(GetHandle());

        public Int32 GetFractionTicks() =>
            TimespanImplementation.Timespan_GetFractionTicksImplementation(GetHandle());

        public Int32 GetHours() =>
            TimespanImplementation.Timespan_GetHoursImplementation(GetHandle());

        public Int32 GetMinutes() =>
            TimespanImplementation.Timespan_GetMinutesImplementation(GetHandle());

        public Int32 GetSeconds() =>
            TimespanImplementation.Timespan_GetSecondsImplementation(GetHandle());

        public Int64 GetTicks() =>
            TimespanImplementation.Timespan_GetTicksImplementation(GetHandle());

        public Double GetTotalDays() =>
            TimespanImplementation.Timespan_GetTotalDaysImplementation(GetHandle());

        public Double GetTotalHours() =>
            TimespanImplementation.Timespan_GetTotalHoursImplementation(GetHandle());

        public Double GetTotalMicroseconds() =>
            TimespanImplementation.Timespan_GetTotalMicrosecondsImplementation(GetHandle());

        public Double GetTotalMilliseconds() =>
            TimespanImplementation.Timespan_GetTotalMillisecondsImplementation(GetHandle());

        public Double GetTotalMinutes() =>
            TimespanImplementation.Timespan_GetTotalMinutesImplementation(GetHandle());

        public Double GetTotalSeconds() =>
            TimespanImplementation.Timespan_GetTotalSecondsImplementation(GetHandle());

        // @TODO
        // ImportTextItem

        public Boolean IsZero() =>
            TimespanImplementation.Timespan_IsZeroImplementation(GetHandle());

        public override string ToString()
        {
            TimespanImplementation.Timespan_ToStringImplementation(GetHandle(), out var OutValue);

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