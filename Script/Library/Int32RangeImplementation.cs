using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32RangeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_EqualityImplementation(FInt32Range A, FInt32Range B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_InequalityImplementation(FInt32Range A, FInt32Range B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_AdjoinsImplementation(FInt32Range InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ConjoinsImplementation(FInt32Range InInt32Range, FInt32Range X,
            FInt32Range Y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContainsElementImplementation(FInt32Range InInt32Range, Int32 Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContainsImplementation(FInt32Range InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContiguousImplementation(FInt32Range InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_GetLowerBoundImplementation(FInt32Range InInt32Range,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetLowerBoundImplementation(FInt32Range InInt32Range,
            FInt32RangeBound NewLowerBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetLowerBoundValueImplementation(FInt32Range InInt32Range,
            Int32 NewLowerBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Range_GetLowerBoundValueImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_GetUpperBoundImplementation(FInt32Range InInt32Range,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetUpperBoundImplementation(FInt32Range InInt32Range,
            FInt32RangeBound NewUpperBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetUpperBoundValueImplementation(FInt32Range InInt32Range,
            Int32 NewUpperBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Range_GetUpperBoundValueImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_HasLowerBoundImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_HasUpperBoundImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_IsDegenerateImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_IsEmptyImplementation(FInt32Range InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_OverlapsImplementation(FInt32Range InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_HullImplementation(FInt32Range X, FInt32Range Y, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_IntersectionImplementation(FInt32Range X, FInt32Range Y,
            out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_AllImplementation(out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_AtLeastImplementation(Int32 Value, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_AtMostImplementation(Int32 Value, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_EmptyImplementation(out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_ExclusiveImplementation(Int32 Min, Int32 Max, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_GreaterThanImplementation(Int32 Value, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_InclusiveImplementation(Int32 Min, Int32 Max, out FInt32Range OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_LessThanImplementation(Int32 Value, out FInt32Range OutValue);
    }
}