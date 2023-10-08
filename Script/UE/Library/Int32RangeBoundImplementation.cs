using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32RangeBoundImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32RangeBound_GetValueImplementation(IntPtr InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_SetValueImplementation(IntPtr InInt32RangeBound,
            Int32 NewValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsClosedImplementation(IntPtr InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsExclusiveImplementation(IntPtr InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsInclusiveImplementation(IntPtr InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsOpenImplementation(IntPtr InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_ExclusiveImplementation(Int32 Value, out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_InclusiveImplementation(Int32 Value, out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_OpenImplementation(out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_FlipInclusionImplementation(IntPtr Bound,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MaxLowerImplementation(IntPtr A, IntPtr B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MaxUpperImplementation(IntPtr A, IntPtr B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MinLowerImplementation(IntPtr A, IntPtr B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MinUpperImplementation(IntPtr A, IntPtr B,
            out FInt32RangeBound OutValue);
    }
}