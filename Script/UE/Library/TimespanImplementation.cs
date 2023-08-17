using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TimespanImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_AddImplementation(IntPtr A, IntPtr B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_NegatedImplementation(IntPtr InTimespan, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_SubtractImplementation(IntPtr A, IntPtr B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_MultiplyImplementation(IntPtr InTimespan, Double Scalar,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_DivideImplementation(IntPtr InTimespan, Double Scalar,
            out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_RemainderImplementation(IntPtr A, IntPtr B, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_GreaterThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_LessThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetDaysImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_GetDurationImplementation(IntPtr InTimespan, out FTimespan OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionMicroImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionMilliImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionNanoImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetFractionTicksImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetHoursImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetMinutesImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Timespan_GetSecondsImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int64 Timespan_GetTicksImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalDaysImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalHoursImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMicrosecondsImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMillisecondsImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalMinutesImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double Timespan_GetTotalSecondsImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Timespan_IsZeroImplementation(IntPtr InTimespan);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Timespan_ToStringImplementation(IntPtr InTimespan, out FString OutValue);

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