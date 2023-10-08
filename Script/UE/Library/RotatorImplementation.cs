using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class RotatorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_AddImplementation(IntPtr A, IntPtr B, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_SubtractImplementation(IntPtr A, IntPtr B, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_MultiplyImplementation(IntPtr A, LwcType Scale, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_IsNearlyZeroImplementation(IntPtr InRotator, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_IsZeroImplementation(IntPtr InRotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_EqualsImplementation(IntPtr A, IntPtr B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_AddDeltaImplementation(IntPtr A, LwcType DeltaPitch, LwcType DeltaYaw,
            LwcType DeltaRoll, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetInverseImplementation(IntPtr InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GridSnapImplementation(IntPtr InRotator, FRotator RotGrid,
            out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_VectorImplementation(IntPtr InRotator, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_QuaternionImplementation(IntPtr InRotator, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_EulerImplementation(IntPtr InRotator, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_RotateVectorImplementation(IntPtr InRotator, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_UnrotateVectorImplementation(IntPtr InRotator, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ClampImplementation(IntPtr InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetNormalizedImplementation(IntPtr InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetDenormalizedImplementation(IntPtr InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_NormalizeImplementation(IntPtr InRotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetWindingAndRemainderImplementation(IntPtr InRotator, out FRotator Winding,
            out FRotator Remainder);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_GetManhattanDistanceImplementation(IntPtr InRotator, FRotator Rotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetEquivalentRotatorImplementation(IntPtr InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_SetClosestToMeImplementation(IntPtr InRotator, out FRotator MakeClosest);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ToStringImplementation(IntPtr InRotator, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ToCompactStringImplementation(IntPtr InRotator, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_InitFromStringImplementation(IntPtr InRotator, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_ContainsNaNImplementation(IntPtr InRotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_ClampAxisImplementation(LwcType Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_NormalizeAxisImplementation(LwcType Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Byte Rotator_CompressAxisToByteImplementation(LwcType Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_DecompressAxisFromByteImplementation(Byte Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt16 Rotator_CompressAxisToShortImplementation(Byte Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_DecompressAxisFromShortImplementation(UInt16 Angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_MakeFromEulerImplementation(FVector Euler, out FRotator OutValue);
    }
}