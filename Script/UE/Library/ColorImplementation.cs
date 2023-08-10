using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class ColorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_DWColorImplementation(IntPtr InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_FromRGBEImplementation(IntPtr InColor, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_FromHexImplementation(FString HexString, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeRandomColorImplementation(out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeRedToGreenColorFromScalarImplementation(Single Scalar, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeFromColorTemperatureImplementation(Single Temp, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_WithAlphaImplementation(IntPtr InColor, SByte Alpha, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ReinterpretAsLinearImplementation(IntPtr InColor, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ToHexImplementation(IntPtr InColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ToStringImplementation(IntPtr InColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_InitFromStringImplementation(IntPtr InColor, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedARGBImplementation(IntPtr InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedABGRImplementation(IntPtr InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedRGBAImplementation(IntPtr InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedBGRAImplementation(IntPtr InColor);
    }
}