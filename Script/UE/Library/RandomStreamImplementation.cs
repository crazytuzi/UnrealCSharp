using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class RandomStreamImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_InitializeImplementation(IntPtr InRandomStream, Int32 InSeed);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_InitializeNameImplementation(IntPtr InRandomStream, FName InName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_ResetImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_GetInitialSeedImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_GenerateNewSeedImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_GetFractionImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 RandomStream_GetUnsignedIntImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_GetUnitVectorImplementation(IntPtr InRandomStream,
            out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_GetCurrentSeedImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_FRandImplementation(IntPtr InRandomStream);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_RandHelperImplementation(IntPtr InRandomStream, Int32 A);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 RandomStream_RandRangeImplementation(IntPtr InRandomStream, Int32 Min,
            Int32 Max);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single RandomStream_FRandRangeImplementation(IntPtr InRandomStream, Single InMin,
            Single InMax);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandImplementation(IntPtr InRandomStream, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandConeHalfAngleImplementation(IntPtr InRandomStream,
            FVector Dir, Single ConeHalfAngleRad, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(
            IntPtr InRandomStream, FVector Dir, Single HorizontalConeHalfAngleRad,
            Single VerticalConeHalfAngleRad, out FVector OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void RandomStream_ToStringImplementation(IntPtr InRandomStream,
            out FString OutValue);
    }
}