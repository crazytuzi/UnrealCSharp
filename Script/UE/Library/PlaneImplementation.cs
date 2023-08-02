using System;
using System.Runtime.CompilerServices;
using Script.Common;
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
        public static extern Boolean Plane_IsValidImplementation(FPlane InPlane);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_GetOriginImplementation(FPlane InPlane, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_GetNormalImplementation(FPlane InPlane, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Plane_PlaneDotImplementation(FPlane InPlane, FVector P);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_NormalizeImplementation(FPlane InPlane, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_FlipImplementation(FPlane InPlane, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByImplementation(FPlane InPlane, FMatrix M, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByUsingAdjointTImplementation(FPlane InPlane, FMatrix M, LwcType DetM,
            FMatrix TA, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_EqualityImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_InequalityImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_EqualsImplementation(FPlane InPlane, FPlane V, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Plane_DotProductImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_AddImplementation(FPlane A, FPlane B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_SubtractImplementation(FPlane A, FPlane B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_DivideImplementation(FPlane InPlane, LwcType Scale, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_MultiplyImplementation(FPlane InPlane, LwcType Scale, out FPlane OutValue);
    }
}