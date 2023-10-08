using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatRangeBoundImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRangeBound_GetValueImplementation(IntPtr InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_SetValueImplementation(IntPtr InFloatRangeBound,
            Single NewValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsClosedImplementation(IntPtr InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsExclusiveImplementation(IntPtr InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsInclusiveImplementation(IntPtr InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsOpenImplementation(IntPtr InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_ExclusiveImplementation(Single Value, out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_InclusiveImplementation(Single Value, out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_OpenImplementation(out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_FlipInclusionImplementation(FFloatRangeBound Bound,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MaxLowerImplementation(IntPtr A, IntPtr B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MaxUpperImplementation(IntPtr A, IntPtr B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MinLowerImplementation(IntPtr A, IntPtr B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MinUpperImplementation(IntPtr A, IntPtr B,
            out FFloatRangeBound OutValue);
    }
}