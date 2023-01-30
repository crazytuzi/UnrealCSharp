using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FrameTimeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_GetFrameImplementation(FFrameTime InFrameTime, out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FrameTime_GetSubFrameImplementation(FFrameTime InFrameTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_FloorToFrameImplementation(FFrameTime InFrameTime,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            FrameTime_CeilToFrameImplementation(FFrameTime InFrameTime, out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_RoundToFrameImplementation(FFrameTime InFrameTime,
            out FFrameNumber OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Double FrameTime_AsDecimalImplementation(FFrameTime InFrameTime);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_FromDecimalImplementation(Double InDecimalFrame, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_EqualityImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_InequalityImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_GreaterThanImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_GreaterThanOrEqualImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_LessThanImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FrameTime_LessThanOrEqualImplementation(FFrameTime A, FFrameTime B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_AddImplementation(FFrameTime A, FFrameTime B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_SubtractImplementation(FFrameTime A, FFrameTime B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            FrameTime_RemainderImplementation(FFrameTime A, FFrameTime B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_NegatedImplementation(FFrameTime InFrameTime, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_MultiplyImplementation(FFrameTime A, FFrameTime B, out FFrameTime OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FrameTime_DivideImplementation(FFrameTime A, FFrameTime B, out FFrameTime OutValue);
    }
}