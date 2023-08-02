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
    public static class RotatorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_AddImplementation(FRotator A, FRotator B, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_SubtractImplementation(FRotator A, FRotator B, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_MultiplyImplementation(FRotator A, LwcType Scale, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_EqualityImplementation(FRotator A, FRotator B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_InequalityImplementation(FRotator A, FRotator B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_IsNearlyZeroImplementation(FRotator InRotator, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_IsZeroImplementation(FRotator InRotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_EqualsImplementation(FRotator A, FRotator B, LwcType Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_AddDeltaImplementation(FRotator A, LwcType DeltaPitch, LwcType DeltaYaw,
            LwcType DeltaRoll, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetInverseImplementation(FRotator InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GridSnapImplementation(FRotator InRotator, FRotator RotGrid,
            out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_VectorImplementation(FRotator InRotator, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_QuaternionImplementation(FRotator InRotator, out FQuat OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_EulerImplementation(FRotator InRotator, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_RotateVectorImplementation(FRotator InRotator, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_UnrotateVectorImplementation(FRotator InRotator, FVector V,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ClampImplementation(FRotator InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetNormalizedImplementation(FRotator InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetDenormalizedImplementation(FRotator InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_NormalizeImplementation(FRotator InRotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetWindingAndRemainderImplementation(FRotator InRotator, out FRotator Winding,
            out FRotator Remainder);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern LwcType Rotator_GetManhattanDistanceImplementation(FRotator InRotator, FRotator Rotator);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_GetEquivalentRotatorImplementation(FRotator InRotator, out FRotator OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_SetClosestToMeImplementation(FRotator InRotator, out FRotator MakeClosest);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ToStringImplementation(FRotator InRotator, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Rotator_ToCompactStringImplementation(FRotator InRotator, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_InitFromStringImplementation(FRotator InRotator, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Rotator_ContainsNaNImplementation(FRotator InRotator);

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