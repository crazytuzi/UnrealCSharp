using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FColor
    {
        public UInt32 DWColor() =>
            ColorImplementation.Color_DWColorImplementation(GetHandle());

        public FLinearColor FromRGBE()
        {
            ColorImplementation.Color_FromRGBEImplementation(GetHandle(), out var OutValue);

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
            ColorImplementation.Color_WithAlphaImplementation(GetHandle(), Alpha, out var OutValue);

            return OutValue;
        }

        public FLinearColor ReinterpretAsLinear()
        {
            ColorImplementation.Color_ReinterpretAsLinearImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString ToHex()
        {
            ColorImplementation.Color_ToHexImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            ColorImplementation.Color_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            ColorImplementation.Color_InitFromStringImplementation(GetHandle(), InSourceString);

        public UInt32 ToPackedARGB() =>
            ColorImplementation.Color_ToPackedARGBImplementation(GetHandle());

        public UInt32 ToPackedABGR() =>
            ColorImplementation.Color_ToPackedABGRImplementation(GetHandle());

        public UInt32 ToPackedRGBA() =>
            ColorImplementation.Color_ToPackedRGBAImplementation(GetHandle());

        public UInt32 ToPackedBGRA() =>
            ColorImplementation.Color_ToPackedBGRAImplementation(GetHandle());
    }
}