using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FrameTimeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_GetFrameImplementation(IntPtr InFrameTime, out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FrameTime_GetSubFrameImplementation(IntPtr InFrameTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_FloorToFrameImplementation(IntPtr InFrameTime,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            FrameTime_CeilToFrameImplementation(IntPtr InFrameTime, out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_RoundToFrameImplementation(IntPtr InFrameTime,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double FrameTime_AsDecimalImplementation(IntPtr InFrameTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_FromDecimalImplementation(Double InDecimalFrame, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_GreaterThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_GreaterThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_LessThanImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_LessThanOrEqualImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_AddImplementation(IntPtr A, IntPtr B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_SubtractImplementation(IntPtr A, IntPtr B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            FrameTime_RemainderImplementation(IntPtr A, IntPtr B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_NegatedImplementation(IntPtr InFrameTime, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_MultiplyImplementation(IntPtr A, IntPtr B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_DivideImplementation(IntPtr A, IntPtr B, out FFrameTime OutValue);
    }
}