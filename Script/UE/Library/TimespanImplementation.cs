using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TimespanImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_AddImplementation(FTimespan A, FTimespan B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_NegatedImplementation(FTimespan InTimespan, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_SubtractImplementation(FTimespan A, FTimespan B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_MultiplyImplementation(FTimespan InTimespan, Double Scalar,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_DivideImplementation(FTimespan InTimespan, Double Scalar,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_RemainderImplementation(FTimespan A, FTimespan B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_EqualityImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_InequalityImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_GreaterThanImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_GreaterThanOrEqualImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_LessThanImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_LessThanOrEqualImplementation(FTimespan A, FTimespan B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetDaysImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_GetDurationImplementation(FTimespan InTimespan, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionMicroImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionMilliImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionNanoImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionTicksImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetHoursImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetMinutesImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetSecondsImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 Timespan_GetTicksImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalDaysImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalHoursImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMicrosecondsImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMillisecondsImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMinutesImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalSecondsImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_IsZeroImplementation(FTimespan InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_ToStringImplementation(FTimespan InTimespan, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromDaysImplementation(Double Days, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromHoursImplementation(Double Hours, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromMicrosecondsImplementation(Double Microseconds, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromMillisecondsImplementation(Double Milliseconds, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromMinutesImplementation(Double Minutes, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_FromSecondsImplementation(Double Seconds, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_MaxValueImplementation(out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_MinValueImplementation(out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_ParseImplementation(FString TimespanString, out FTimespan OutTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_RatioImplementation(FTimespan Dividend, FTimespan Divisor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_ZeroImplementation(out FTimespan OutValue);
    }
}