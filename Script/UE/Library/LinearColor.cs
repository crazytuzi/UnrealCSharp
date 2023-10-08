using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FLinearColor
    {
        public FColor ToRGBE()
        {
            LinearColorImplementation.LinearColor_ToRGBEImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FLinearColor FromSRGBColor(FColor Color)
        {
            LinearColorImplementation.LinearColor_FromSRGBColorImplementation(Color, out var OutValue);

            return OutValue;
        }

        public static FLinearColor FromPow22Color(FColor Color)
        {
            LinearColorImplementation.LinearColor_FromPow22ColorImplementation(Color, out var OutValue);

            return OutValue;
        }

        public Single Component(Int32 Index) =>
            LinearColorImplementation.LinearColor_ComponentImplementation(GetHandle(), Index);

        public static FLinearColor operator +(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator -(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_SubtractImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator *(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_MultiplyImplementation(A.GetHandle(), B.GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator *(FLinearColor A, Single Scalar)
        {
            LinearColorImplementation.LinearColor_MultiplyScalarImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator /(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_DivideImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator /(FLinearColor A, Single Scalar)
        {
            LinearColorImplementation.LinearColor_DivideScalarImplementation(A.GetHandle(), Scalar, out var OutValue);

            return OutValue;
        }

        public FLinearColor GetClamped(Single InMin = 0.0f, Single InMax = 0.0f)
        {
            LinearColorImplementation.LinearColor_GetClampedImplementation(GetHandle(), InMin, InMax, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FLinearColor ColorB, Single Tolerance) =>
            LinearColorImplementation.LinearColor_EqualsImplementation(GetHandle(), ColorB.GetHandle(), Tolerance);

        public FLinearColor CopyWithNewOpacity(Single NewOpacicty)
        {
            LinearColorImplementation.LinearColor_CopyWithNewOpacityImplementation(GetHandle(), NewOpacicty,
                out var OutValue);

            return OutValue;
        }

        public static FLinearColor MakeFromHSV8(SByte H, SByte S, SByte V)
        {
            LinearColorImplementation.LinearColor_MakeFromHSV8Implementation(H, S, V, out var OutValue);

            return OutValue;
        }

        public static FLinearColor MakeRandomColor()
        {
            LinearColorImplementation.LinearColor_MakeRandomColorImplementation(out var OutValue);

            return OutValue;
        }

        public static FLinearColor MakeFromColorTemperature(Single Temp)
        {
            LinearColorImplementation.LinearColor_MakeFromColorTemperatureImplementation(Temp, out var OutValue);

            return OutValue;
        }

        public static Single Dist(FLinearColor V1, FLinearColor V2) =>
            LinearColorImplementation.LinearColor_DistImplementation(V1.GetHandle(), V2.GetHandle());

        // @TODO
        // EvaluateBezier

        public FLinearColor LinearRGBToHSV()
        {
            LinearColorImplementation.LinearColor_LinearRGBToHSVImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FLinearColor HSVToLinearRGB()
        {
            LinearColorImplementation.LinearColor_HSVToLinearRGBImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FLinearColor LerpUsingHSV(FLinearColor From, FLinearColor To, Single Progress)
        {
            LinearColorImplementation.LinearColor_LerpUsingHSVImplementation(From, To, Progress, out var OutValue);

            return OutValue;
        }

#if UE_5_0_OR_LATER
        public FColor QuantizeFloor()
        {
            LinearColorImplementation.LinearColor_QuantizeFloorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }
#endif

#if UE_5_0_OR_LATER
        [Obsolete(
            "Most callers of Quantize should have been calling QuantizeRound; to match old behavior use QuantizeFloor",
            false)]
#endif
        public FColor Quantize()
        {
            LinearColorImplementation.LinearColor_QuantizeImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FColor QuantizeRound()
        {
            LinearColorImplementation.LinearColor_QuantizeRoundImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FColor ToFColor(Boolean bSRGB)
        {
            LinearColorImplementation.LinearColor_ToFColorImplementation(GetHandle(), bSRGB, out var OutValue);

            return OutValue;
        }

        public FLinearColor Desaturate(Single Desaturation)
        {
            LinearColorImplementation.LinearColor_DesaturateImplementation(GetHandle(), Desaturation, out var OutValue);

            return OutValue;
        }

#if UE_5_0_OR_LATER
        [Obsolete("", true)]
#endif
        public Single ComputeLuminance() =>
            LinearColorImplementation.LinearColor_ComputeLuminanceImplementation(GetHandle());

        public Single GetMax() =>
            LinearColorImplementation.LinearColor_GetMaxImplementation(GetHandle());

        public Boolean IsAlmostBlack() =>
            LinearColorImplementation.LinearColor_IsAlmostBlackImplementation(GetHandle());

        public Single GetMin() =>
            LinearColorImplementation.LinearColor_GetMinImplementation(GetHandle());

        public Single GetLuminance() =>
            LinearColorImplementation.LinearColor_GetLuminanceImplementation(GetHandle());

        public override string ToString()
        {
            LinearColorImplementation.LinearColor_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            LinearColorImplementation.LinearColor_InitFromStringImplementation(GetHandle(), InSourceString);
    }
}