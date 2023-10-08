using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FPrimaryAssetId
    {
        public static FPrimaryAssetId ParseTypeAndName(FName TypeAndName)
        {
            PrimaryAssetIdImplementation.PrimaryAssetId_ParseTypeAndNameNameImplementation(TypeAndName,
                out var OutValue);

            return OutValue;
        }

        public static FPrimaryAssetId ParseTypeAndName(FString TypeAndName)
        {
            PrimaryAssetIdImplementation.PrimaryAssetId_ParseTypeAndNameStringImplementation(TypeAndName,
                out var OutValue);

            return OutValue;
        }

        public Boolean IsValid() =>
            PrimaryAssetIdImplementation.PrimaryAssetId_IsValidImplementation(GetHandle());

        public override string ToString()
        {
            PrimaryAssetIdImplementation.PrimaryAssetId_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public static FPrimaryAssetId FromString(FString String)
        {
            PrimaryAssetIdImplementation.PrimaryAssetId_FromStringImplementation(String, out var OutValue);

            return OutValue;
        }
    }
}