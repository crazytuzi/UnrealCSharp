using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class Vector4Implementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_GetComponentImplementation(IntPtr InVector4, Int32 ComponentIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SetComponentImplementation(IntPtr InVector4, Int32 ComponentIndex,
            LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_NegatedImplementation(IntPtr InVector4, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_AddImplementation(IntPtr A, IntPtr B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SubtractImplementation(IntPtr A, IntPtr B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_MultiplyScaleImplementation(IntPtr InVector4, LwcType Scale,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_DivideScaleImplementation(IntPtr InVector4, LwcType Scale,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_DivideImplementation(IntPtr A, IntPtr B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_MultiplyImplementation(IntPtr A, IntPtr B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Dot3Implementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Dot4Implementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_CrossProductImplementation(IntPtr A, IntPtr B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_ComponentImplementation(IntPtr InVector4, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_IsUnit3Implementation(IntPtr InVector4, LwcType LengthSquaredTolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToStringImplementation(IntPtr InVector4, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_InitFromStringImplementation(IntPtr InVector4, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_GetSafeNormalImplementation(IntPtr InVector4, LwcType Tolerance,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_GetUnsafeNormal3Implementation(IntPtr InVector4, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToOrientationRotatorImplementation(IntPtr InVector4, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToOrientationQuatImplementation(IntPtr InVector4, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_RotationImplementation(IntPtr InVector4, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SetImplementation(IntPtr InVector4, LwcType InX, LwcType InY, LwcType InZ,
            LwcType InW);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Size3Implementation(IntPtr InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeSquared3Implementation(IntPtr InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeImplementation(IntPtr InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeSquaredImplementation(IntPtr InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_ContainsNaNImplementation(IntPtr InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_IsNearlyZero3Implementation(IntPtr InVector4, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_Reflect3Implementation(IntPtr InVector4, FVector4 Normal,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_FindBestAxisVectors3Implementation(IntPtr InVector4, out FVector4 Axis1,
            out FVector4 Axis2);
    }
}