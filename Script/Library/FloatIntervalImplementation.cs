using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatIntervalImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatInterval_SizeImplementation(FFloatInterval InFloatInterval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatInterval_IsValidImplementation(FFloatInterval InFloatInterval);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatInterval_ContainsImplementation(FFloatInterval InFloatInterval,
            Single Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_ExpandImplementation(FFloatInterval InFloatInterval,
            Single ExpandAmount);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_IncludeImplementation(FFloatInterval InFloatInterval, Single X);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatInterval_InterpolateImplementation(FFloatInterval InFloatInterval,
            Single Alpha);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatInterval_IntersectImplementation(FFloatInterval A, FFloatInterval B,
            out FFloatInterval OutValue);
    }
}