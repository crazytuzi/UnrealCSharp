using System;
using System.Runtime.CompilerServices;
using Script.CoreUObject;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.Library
{
    public static class PlaneImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_IsValidImplementation(IntPtr InPlane);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_GetOriginImplementation(IntPtr InPlane, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_GetNormalImplementation(IntPtr InPlane, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Plane_PlaneDotImplementation(IntPtr InPlane, FVector P);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_NormalizeImplementation(IntPtr InPlane, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_FlipImplementation(IntPtr InPlane, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByImplementation(IntPtr InPlane, FMatrix M, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByUsingAdjointTImplementation(IntPtr InPlane, FMatrix M, LwcType DetM,
            FMatrix TA, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_EqualsImplementation(IntPtr InPlane, FPlane V, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Plane_DotProductImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_AddImplementation(IntPtr A, IntPtr B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_SubtractImplementation(IntPtr A, IntPtr B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_DivideImplementation(IntPtr InPlane, LwcType Scale, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_MultiplyImplementation(IntPtr InPlane, LwcType Scale, out FPlane OutValue);
    }
}