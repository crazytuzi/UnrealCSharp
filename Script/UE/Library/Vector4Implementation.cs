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
    public static class Vector4Implementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_GetComponentImplementation(FVector4 InVector4, Int32 ComponentIndex);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SetComponentImplementation(FVector4 InVector4, Int32 ComponentIndex,
            LwcType InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_NegatedImplementation(FVector4 InVector4, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_AddImplementation(FVector4 A, FVector4 B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SubtractImplementation(FVector4 A, FVector4 B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_MultiplyScaleImplementation(FVector4 InVector4, LwcType Scale,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_DivideScaleImplementation(FVector4 InVector4, LwcType Scale,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_DivideImplementation(FVector4 A, FVector4 B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_MultiplyImplementation(FVector4 A, FVector4 B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Dot3Implementation(FVector4 A, FVector4 B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Dot4Implementation(FVector4 A, FVector4 B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_EqualityImplementation(FVector4 A, FVector4 B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_InequalityImplementation(FVector4 A, FVector4 B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_CrossProductImplementation(FVector4 A, FVector4 B, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_ComponentImplementation(FVector4 InVector4, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_EqualsImplementation(FVector4 A, FVector4 B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_IsUnit3Implementation(FVector4 InVector4, LwcType LengthSquaredTolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToStringImplementation(FVector4 InVector4, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_InitFromStringImplementation(FVector4 InVector4, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_GetSafeNormalImplementation(FVector4 InVector4, LwcType Tolerance,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_GetUnsafeNormal3Implementation(FVector4 InVector4, out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToOrientationRotatorImplementation(FVector4 InVector4, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_ToOrientationQuatImplementation(FVector4 InVector4, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_RotationImplementation(FVector4 InVector4, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_SetImplementation(FVector4 InVector4, LwcType InX, LwcType InY, LwcType InZ,
            LwcType InW);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_Size3Implementation(FVector4 InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeSquared3Implementation(FVector4 InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeImplementation(FVector4 InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Vector4_SizeSquaredImplementation(FVector4 InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_ContainsNaNImplementation(FVector4 InVector4);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Vector4_IsNearlyZero3Implementation(FVector4 InVector4, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_Reflect3Implementation(FVector4 InVector4, FVector4 Normal,
            out FVector4 OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Vector4_FindBestAxisVectors3Implementation(FVector4 InVector4, out FVector4 Axis1,
            out FVector4 Axis2);
    }
}