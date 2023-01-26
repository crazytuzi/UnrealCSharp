using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class FloatRangeBoundImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_EqualityImplementation(FFloatRangeBound A, FFloatRangeBound B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_InequalityImplementation(FFloatRangeBound A, FFloatRangeBound B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single FloatRangeBound_GetValueImplementation(FFloatRangeBound InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_SetValueImplementation(FFloatRangeBound InFloatRangeBound,
            Single NewValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsClosedImplementation(FFloatRangeBound InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsExclusiveImplementation(FFloatRangeBound InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsInclusiveImplementation(FFloatRangeBound InFloatRangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean FloatRangeBound_IsOpenImplementation(FFloatRangeBound InFloatRangeBound);

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
        public static extern void FloatRangeBound_MaxLowerImplementation(FFloatRangeBound A, FFloatRangeBound B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MaxUpperImplementation(FFloatRangeBound A, FFloatRangeBound B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MinLowerImplementation(FFloatRangeBound A, FFloatRangeBound B,
            out FFloatRangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FloatRangeBound_MinUpperImplementation(FFloatRangeBound A, FFloatRangeBound B,
            out FFloatRangeBound OutValue);
    }
}