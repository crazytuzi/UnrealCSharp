using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class ColorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_DWColorImplementation(FColor InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_EqualityImplementation(FColor A, FColor B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_InequalityImplementation(FColor A, FColor B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_FromRGBEImplementation(FColor InColor, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_FromHexImplementation(FString HexString, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeRandomColorImplementation(out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeRedToGreenColorFromScalarImplementation(Single Scalar, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_MakeFromColorTemperatureImplementation(Single Temp, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_WithAlphaImplementation(FColor InColor, SByte Alpha, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ReinterpretAsLinearImplementation(FColor InColor, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ToHexImplementation(FColor InColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Color_ToStringImplementation(FColor InColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean Color_InitFromStringImplementation(FColor InColor, FString InSourceString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedARGBImplementation(FColor InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedABGRImplementation(FColor InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedRGBAImplementation(FColor InColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UInt32 Color_ToPackedBGRAImplementation(FColor InColor);
    }
}