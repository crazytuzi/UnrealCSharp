using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatRangeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_EqualityImplementation(FFloatRange A, FFloatRange B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_InequalityImplementation(FFloatRange A, FFloatRange B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_AdjoinsImplementation(FFloatRange InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ConjoinsImplementation(FFloatRange InFloatRange, FFloatRange X,
            FFloatRange Y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContainsElementImplementation(FFloatRange InFloatRange, Single Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContainsImplementation(FFloatRange InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_ContiguousImplementation(FFloatRange InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_GetLowerBoundImplementation(FFloatRange InFloatRange,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetLowerBoundImplementation(FFloatRange InFloatRange,
            FFloatRangeBound NewLowerBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetLowerBoundValueImplementation(FFloatRange InFloatRange,
            Single NewLowerBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRange_GetLowerBoundValueImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_GetUpperBoundImplementation(FFloatRange InFloatRange,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetUpperBoundImplementation(FFloatRange InFloatRange,
            FFloatRangeBound NewUpperBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_SetUpperBoundValueImplementation(FFloatRange InFloatRange,
            Single NewUpperBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRange_GetUpperBoundValueImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_HasLowerBoundImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_HasUpperBoundImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_IsDegenerateImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_IsEmptyImplementation(FFloatRange InFloatRange);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRange_OverlapsImplementation(FFloatRange InFloatRange, FFloatRange Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_HullImplementation(FFloatRange X, FFloatRange Y, out FFloatRange OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRange_IntersectionImplementation(FFloatRange X, FFloatRange Y,
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