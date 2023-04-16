using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FrameNumberImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_IncrementImplementation(FFrameNumber InFrameNumber);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_DecrementImplementation(FFrameNumber InFrameNumber);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_EqualityImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_InequalityImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_LessThanImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_GreaterThanImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_LessThanOrEqualImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_GreaterThanOrEqualImplementation(FFrameNumber A, FFrameNumber B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_AddImplementation(FFrameNumber A, FFrameNumber B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_SubtractImplementation(FFrameNumber A, FFrameNumber B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_RemainderImplementation(FFrameNumber A, FFrameNumber B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_NegatedImplementation(FFrameNumber InFrameNumber,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_MultiplyImplementation(FFrameNumber InFrameNumber, Single Scalar,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_DivideImplementation(FFrameNumber InFrameNumber, Single Scalar,
            out FFrameNumber OutValue);
    }
}