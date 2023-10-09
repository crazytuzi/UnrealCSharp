using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FrameNumberImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_IncrementImplementation(IntPtr InFrameNumber);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_DecrementImplementation(IntPtr InFrameNumber);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_LessThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameNumber_GreaterThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_AddImplementation(IntPtr A, IntPtr B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_SubtractImplementation(IntPtr A, IntPtr B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_RemainderImplementation(IntPtr A, IntPtr B,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_NegatedImplementation(IntPtr InFrameNumber,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_MultiplyImplementation(IntPtr InFrameNumber, Single Scalar,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameNumber_DivideImplementation(IntPtr InFrameNumber, Single Scalar,
            out FFrameNumber OutValue);
    }
}