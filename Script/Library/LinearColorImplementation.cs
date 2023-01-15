using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class LinearColorImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToRGBEImplementation(FLinearColor InLinearColor, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_FromSRGBColorImplementation(FColor Color, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_FromPow22ColorImplementation(FColor Color, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_ComponentImplementation(FLinearColor InLinearColor, Int32 Index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_AddImplementation(FLinearColor A, FLinearColor B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_SubtractImplementation(FLinearColor A, FLinearColor B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MultiplyImplementation(FLinearColor A, FLinearColor B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_MultiplyScalarImplementation(FLinearColor InLinearColor, Single Scalar,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DivideImplementation(FLinearColor A, FLinearColor B,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DivideScalarImplementation(FLinearColor InLinearColor, Single Scalar,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_GetClampedImplementation(FLinearColor InLinearColor, Single InMin,
            Single InMax, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_EqualityImplementation(FLinearColor A, FLinearColor B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_InequalityImplementation(FLinearColor A, FLinearColor B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_EqualsImplementation(FLinearColor A, FLinearColor B, Single Tolerance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_CopyWithNewOpacityImplementation(FLinearColor InLinearColor,
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
        public static extern Single LinearColor_DistImplementation(FLinearColor V1, FLinearColor V2);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_LinearRGBToHSVImplementation(FLinearColor InLinearColor,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_HSVToLinearRGBImplementation(FLinearColor InLinearColor,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_LerpUsingHSVImplementation(FLinearColor From, FLinearColor To,
            Single Progress, out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_QuantizeImplementation(FLinearColor InLinearColor, out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_QuantizeRoundImplementation(FLinearColor InLinearColor,
            out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToFColorImplementation(FLinearColor InLinearColor, Boolean bSRGB,
            out FColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_DesaturateImplementation(FLinearColor InLinearColor, Single Desaturation,
            out FLinearColor OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_ComputeLuminanceImplementation(FLinearColor InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetMaxImplementation(FLinearColor InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_IsAlmostBlackImplementation(FLinearColor InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetMinImplementation(FLinearColor InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Single LinearColor_GetLuminanceImplementation(FLinearColor InLinearColor);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LinearColor_ToStringImplementation(FLinearColor InLinearColor, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LinearColor_InitFromStringImplementation(FLinearColor InLinearColor,
            FString InSourceString);
    }
}