using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FLinearColor
    {
        public FColor ToRGBE()
        {
            LinearColorImplementation.LinearColor_ToRGBEImplementation(this, out var OutValue);

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
            LinearColorImplementation.LinearColor_ComponentImplementation(this, Index);

        public static FLinearColor operator +(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator -(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator *(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator *(FLinearColor A, Single Scalar)
        {
            LinearColorImplementation.LinearColor_MultiplyScalarImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator /(FLinearColor A, FLinearColor B)
        {
            LinearColorImplementation.LinearColor_DivideImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FLinearColor operator /(FLinearColor A, Single Scalar)
        {
            LinearColorImplementation.LinearColor_DivideScalarImplementation(A, Scalar, out var OutValue);

            return OutValue;
        }

        public FLinearColor GetClamped(Single InMin = 0.0f, Single InMax = 0.0f)
        {
            LinearColorImplementation.LinearColor_GetClampedImplementation(this, InMin, InMax, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FLinearColor A, FLinearColor B) =>
            LinearColorImplementation.LinearColor_EqualityImplementation(A, B);

        public static Boolean operator !=(FLinearColor A, FLinearColor B) =>
            LinearColorImplementation.LinearColor_InequalityImplementation(A, B);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FLinearColor ColorB, Single Tolerance) =>
            LinearColorImplementation.LinearColor_EqualsImplementation(this, ColorB, Tolerance);

        public FLinearColor CopyWithNewOpacity(Single NewOpacicty)
        {
            LinearColorImplementation.LinearColor_CopyWithNewOpacityImplementation(this, NewOpacicty, out var OutValue);

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
            LinearColorImplementation.LinearColor_DistImplementation(V1, V2);

        // @TODO
        // EvaluateBezier

        public FLinearColor LinearRGBToHSV()
        {
            LinearColorImplementation.LinearColor_LinearRGBToHSVImplementation(this, out var OutValue);

            return OutValue;
        }

        public FLinearColor HSVToLinearRGB()
        {
            LinearColorImplementation.LinearColor_HSVToLinearRGBImplementation(this, out var OutValue);

            return OutValue;
        }

        public static FLinearColor LerpUsingHSV(FLinearColor From, FLinearColor To, Single Progress)
        {
            LinearColorImplementation.LinearColor_LerpUsingHSVImplementation(From, To, Progress, out var OutValue);

            return OutValue;
        }

        public FColor Quantize()
        {
            LinearColorImplementation.LinearColor_QuantizeImplementation(this, out var OutValue);

            return OutValue;
        }

        public FColor QuantizeRound()
        {
            LinearColorImplementation.LinearColor_QuantizeRoundImplementation(this, out var OutValue);

            return OutValue;
        }

        public FColor ToFColor(Boolean bSRGB)
        {
            LinearColorImplementation.LinearColor_ToFColorImplementation(this, bSRGB, out var OutValue);

            return OutValue;
        }

        public FLinearColor Desaturate(Single Desaturation)
        {
            LinearColorImplementation.LinearColor_DesaturateImplementation(this, Desaturation, out var OutValue);

            return OutValue;
        }

        public Single ComputeLuminance() =>
            LinearColorImplementation.LinearColor_ComputeLuminanceImplementation(this);

        public Single GetMax() =>
            LinearColorImplementation.LinearColor_GetMaxImplementation(this);

        public Boolean IsAlmostBlack() =>
            LinearColorImplementation.LinearColor_IsAlmostBlackImplementation(this);

        public Single GetMin() =>
            LinearColorImplementation.LinearColor_GetMinImplementation(this);

        public Single GetLuminance() =>
            LinearColorImplementation.LinearColor_GetLuminanceImplementation(this);

        public FString ToString()
        {
            LinearColorImplementation.LinearColor_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            LinearColorImplementation.LinearColor_InitFromStringImplementation(this, InSourceString);
    }
}