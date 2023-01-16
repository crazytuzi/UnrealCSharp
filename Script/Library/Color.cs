using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FColor
    {
        public UInt32 DWColor() =>
            ColorImplementation.Color_DWColorImplementation(this);

        public static Boolean operator ==(FColor A, FColor B) =>
            ColorImplementation.Color_EqualityImplementation(A, B);

        public static Boolean operator !=(FColor A, FColor B) =>
            ColorImplementation.Color_InequalityImplementation(A, B);

        public FLinearColor FromRGBE()
        {
            ColorImplementation.Color_FromRGBEImplementation(this, out var OutValue);

            return OutValue;
        }

        public static FColor FromHex(FString HexString)
        {
            ColorImplementation.Color_FromHexImplementation(HexString, out var OutValue);

            return OutValue;
        }

        public static FColor MakeRandomColor()
        {
            ColorImplementation.Color_MakeRandomColorImplementation(out var OutValue);

            return OutValue;
        }

        public static FColor MakeRedToGreenColorFromScalar(Single Scalar)
        {
            ColorImplementation.Color_MakeRedToGreenColorFromScalarImplementation(Scalar, out var OutValue);

            return OutValue;
        }

        public static FColor MakeFromColorTemperature(Single Temp)
        {
            ColorImplementation.Color_MakeFromColorTemperatureImplementation(Temp, out var OutValue);

            return OutValue;
        }

        public FColor WithAlpha(SByte Alpha)
        {
            ColorImplementation.Color_WithAlphaImplementation(this, Alpha, out var OutValue);

            return OutValue;
        }

        public FLinearColor ReinterpretAsLinear()
        {
            ColorImplementation.Color_ReinterpretAsLinearImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ToHex()
        {
            ColorImplementation.Color_ToHexImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ToString()
        {
            ColorImplementation.Color_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            ColorImplementation.Color_InitFromStringImplementation(this, InSourceString);

        public UInt32 ToPackedARGB() =>
            ColorImplementation.Color_ToPackedARGBImplementation(this);

        public UInt32 ToPackedABGR() =>
            ColorImplementation.Color_ToPackedABGRImplementation(this);

        public UInt32 ToPackedRGBA() =>
            ColorImplementation.Color_ToPackedRGBAImplementation(this);

        public UInt32 ToPackedBGRA() =>
            ColorImplementation.Color_ToPackedBGRAImplementation(this);
    }
}