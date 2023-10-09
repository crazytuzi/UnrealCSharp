using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32RangeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_AdjoinsImplementation(IntPtr InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ConjoinsImplementation(IntPtr InInt32Range, FInt32Range X,
            FInt32Range Y);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContainsElementImplementation(IntPtr InInt32Range, Int32 Element);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContainsImplementation(IntPtr InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_ContiguousImplementation(IntPtr InInt32Range, FInt32Range Other);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_GetLowerBoundImplementation(IntPtr InInt32Range,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetLowerBoundImplementation(IntPtr InInt32Range,
            FInt32RangeBound NewLowerBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetLowerBoundValueImplementation(IntPtr InInt32Range,
            Int32 NewLowerBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Range_GetLowerBoundValueImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_GetUpperBoundImplementation(IntPtr InInt32Range,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetUpperBoundImplementation(IntPtr InInt32Range,
            FInt32RangeBound NewUpperBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32Range_SetUpperBoundValueImplementation(IntPtr InInt32Range,
            Int32 NewUpperBoundValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32Range_GetUpperBoundValueImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_HasLowerBoundImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_HasUpperBoundImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_IsDegenerateImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_IsEmptyImplementation(IntPtr InInt32Range);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32Range_OverlapsImplementation(IntPtr InInt32Range, FInt32Range Other);

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