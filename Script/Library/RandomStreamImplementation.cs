using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class RandomStreamImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_InitializeImplementation(FRandomStream InRandomStream, Int32 InSeed);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_InitializeNameImplementation(FRandomStream InRandomStream, FName InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_ResetImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_GetInitialSeedImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_GenerateNewSeedImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_GetFractionImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 RandomStream_GetUnsignedIntImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_GetUnitVectorImplementation(FRandomStream InRandomStream,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_GetCurrentSeedImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_FRandImplementation(FRandomStream InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_RandHelperImplementation(FRandomStream InRandomStream, Int32 A);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_RandRangeImplementation(FRandomStream InRandomStream, Int32 Min,
            Int32 Max);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_FRandRangeImplementation(FRandomStream InRandomStream, Single InMin,
            Single InMax);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandImplementation(FRandomStream InRandomStream, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandConeHalfAngleImplementation(FRandomStream InRandomStream,
            FVector Dir, Single ConeHalfAngleRad, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
            FRandomStream InRandomStream, FVector Dir, Single HorizontalConeHalfAngleRad,
            Single VerticalConeHalfAngleRad, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_ToStringImplementation(FRandomStream InRandomStream,
            out FString OutValue);
    }
}