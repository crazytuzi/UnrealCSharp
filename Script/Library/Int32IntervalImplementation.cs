using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32IntervalImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Interval_SizeImplementation(FInt32Interval InInt32Interval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Interval_IsValidImplementation(FInt32Interval InInt32Interval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Interval_ContainsImplementation(FInt32Interval InInt32Interval,
            Int32 Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_ExpandImplementation(FInt32Interval InInt32Interval,
            Int32 ExpandAmount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_IncludeImplementation(FInt32Interval InInt32Interval, Int32 X);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Interval_InterpolateImplementation(FInt32Interval InInt32Interval,
            Single Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Interval_IntersectImplementation(FInt32Interval A, FInt32Interval B,
            out FInt32Interval OutValue);
    }
}