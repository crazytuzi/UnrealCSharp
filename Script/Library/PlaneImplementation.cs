using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

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
        public static extern Single Plane_PlaneDotImplementation(FPlane InPlane, FVector P);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_NormalizeImplementation(FPlane InPlane, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_FlipImplementation(FPlane InPlane, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByImplementation(FPlane InPlane, FMatrix M, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_TransformByUsingAdjointTImplementation(FPlane InPlane, FMatrix M, Single DetM,
            FMatrix TA, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_EqualityImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_InequalityImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Plane_EqualsImplementation(FPlane InPlane, FPlane V, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single Plane_DotProductImplementation(FPlane A, FPlane B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_AddImplementation(FPlane A, FPlane B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_SubtractImplementation(FPlane A, FPlane B, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_DivideImplementation(FPlane InPlane, Single Scale, out FPlane OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Plane_MultiplyImplementation(FPlane InPlane, Single Scale, out FPlane OutValue);
    }
}