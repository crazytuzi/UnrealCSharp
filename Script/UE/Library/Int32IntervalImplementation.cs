using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32IntervalImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Interval_SizeImplementation(IntPtr InInt32Interval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Interval_IsValidImplementation(IntPtr InInt32Interval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Interval_ContainsImplementation(IntPtr InInt32Interval,
            Int32 Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_ExpandImplementation(IntPtr InInt32Interval,
            Int32 ExpandAmount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_IncludeImplementation(IntPtr InInt32Interval, Int32 X);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Interval_InterpolateImplementation(IntPtr InInt32Interval,
            Single Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_IntersectImplementation(IntPtr A, IntPtr B,
            out FInt32Interval OutValue);
    }
}