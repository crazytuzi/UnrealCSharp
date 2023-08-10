using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class LinearColorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToRGBEImplementation(IntPtr InLinearColor, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_FromSRGBColorImplementation(FColor Color, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_FromPow22ColorImplementation(FColor Color, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_ComponentImplementation(IntPtr InLinearColor, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_AddImplementation(IntPtr A, IntPtr B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_SubtractImplementation(IntPtr A, IntPtr B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MultiplyImplementation(IntPtr A, IntPtr B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MultiplyScalarImplementation(IntPtr InLinearColor, Single Scalar,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DivideImplementation(IntPtr A, IntPtr B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DivideScalarImplementation(IntPtr InLinearColor, Single Scalar,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_GetClampedImplementation(IntPtr InLinearColor, Single InMin,
            Single InMax, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_EqualsImplementation(IntPtr A, IntPtr B, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_CopyWithNewOpacityImplementation(IntPtr InLinearColor,
            Single NewOpacicty, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MakeFromHSV8Implementation(SByte H, SByte S, SByte V,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MakeRandomColorImplementation(out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MakeFromColorTemperatureImplementation(Single Temp,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_DistImplementation(IntPtr V1, IntPtr V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_LinearRGBToHSVImplementation(IntPtr InLinearColor,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_HSVToLinearRGBImplementation(IntPtr InLinearColor,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_LerpUsingHSVImplementation(FLinearColor From, FLinearColor To,
            Single Progress, out FLinearColor OutValue);

#if UE_5_0_OR_LATER
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_QuantizeFloorImplementation(IntPtr InLinearColor,
            out FColor OutValue);
#endif

#if UE_5_0_OR_LATER
        [Obsolete(
            "Most callers of Quantize should have been calling QuantizeRound; to match old behavior use QuantizeFloor",
            false)]
#endif
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_QuantizeImplementation(IntPtr InLinearColor, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_QuantizeRoundImplementation(IntPtr InLinearColor,
            out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToFColorImplementation(IntPtr InLinearColor, Boolean bSRGB,
            out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DesaturateImplementation(IntPtr InLinearColor, Single Desaturation,
            out FLinearColor OutValue);

#if UE_5_0_OR_LATER
        [Obsolete("", true)]
#endif
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_ComputeLuminanceImplementation(IntPtr InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetMaxImplementation(IntPtr InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_IsAlmostBlackImplementation(IntPtr InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetMinImplementation(IntPtr InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetLuminanceImplementation(IntPtr InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToStringImplementation(IntPtr InLinearColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_InitFromStringImplementation(IntPtr InLinearColor,
            FString InSourceString);
    }
}