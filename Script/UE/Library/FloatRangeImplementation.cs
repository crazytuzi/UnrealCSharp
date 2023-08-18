using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatRangeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_AdjoinsImplementation(IntPtr InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ConjoinsImplementation(IntPtr InFloatRange, FFloatRange X,
            FFloatRange Y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContainsElementImplementation(IntPtr InFloatRange, Single Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContainsImplementation(IntPtr InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContiguousImplementation(IntPtr InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_GetLowerBoundImplementation(IntPtr InFloatRange,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetLowerBoundImplementation(IntPtr InFloatRange,
            FFloatRangeBound NewLowerBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetLowerBoundValueImplementation(IntPtr InFloatRange,
            Single NewLowerBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRange_GetLowerBoundValueImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_GetUpperBoundImplementation(IntPtr InFloatRange,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetUpperBoundImplementation(IntPtr InFloatRange,
            FFloatRangeBound NewUpperBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetUpperBoundValueImplementation(IntPtr InFloatRange,
            Single NewUpperBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRange_GetUpperBoundValueImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_HasLowerBoundImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_HasUpperBoundImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_IsDegenerateImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_IsEmptyImplementation(IntPtr InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_OverlapsImplementation(IntPtr InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_HullImplementation(IntPtr X, IntPtr Y, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_IntersectionImplementation(IntPtr X, IntPtr Y,
            out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_AllImplementation(out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_AtLeastImplementation(Single Value, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_AtMostImplementation(Single Value, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_EmptyImplementation(out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_ExclusiveImplementation(Single Min, Single Max, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_GreaterThanImplementation(Single Value, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_InclusiveImplementation(Single Min, Single Max, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_LessThanImplementation(Single Value, out FFloatRange OutValue);
    }
}