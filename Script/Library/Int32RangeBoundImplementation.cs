using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Int32RangeBoundImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_EqualityImplementation(FInt32RangeBound A, FInt32RangeBound B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_InequalityImplementation(FInt32RangeBound A, FInt32RangeBound B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 Int32RangeBound_GetValueImplementation(FInt32RangeBound InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_SetValueImplementation(FInt32RangeBound InInt32RangeBound,
            Int32 NewValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsClosedImplementation(FInt32RangeBound InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsExclusiveImplementation(FInt32RangeBound InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsInclusiveImplementation(FInt32RangeBound InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Int32RangeBound_IsOpenImplementation(FInt32RangeBound InInt32RangeBound);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_ExclusiveImplementation(Int32 Value, out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_InclusiveImplementation(Int32 Value, out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_OpenImplementation(out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_FlipInclusionImplementation(FInt32RangeBound Bound,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MaxLowerImplementation(FInt32RangeBound A, FInt32RangeBound B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MaxUpperImplementation(FInt32RangeBound A, FInt32RangeBound B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MinLowerImplementation(FInt32RangeBound A, FInt32RangeBound B,
            out FInt32RangeBound OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Int32RangeBound_MinUpperImplementation(FInt32RangeBound A, FInt32RangeBound B,
            out FInt32RangeBound OutValue);
    }
}