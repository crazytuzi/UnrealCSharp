using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatIntervalImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatInterval_SizeImplementation(IntPtr InFloatInterval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatInterval_IsValidImplementation(IntPtr InFloatInterval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatInterval_ContainsImplementation(IntPtr InFloatInterval,
            Single Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_ExpandImplementation(IntPtr InFloatInterval,
            Single ExpandAmount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_IncludeImplementation(IntPtr InFloatInterval, Single X);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatInterval_InterpolateImplementation(IntPtr InFloatInterval,
            Single Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_IntersectImplementation(IntPtr A, IntPtr B,
            out FFloatInterval OutValue);
    }
}