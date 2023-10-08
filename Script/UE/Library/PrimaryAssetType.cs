using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FPrimaryAssetType
    {
        public FName GetName()
        {
            PrimaryAssetTypeImplementation.PrimaryAssetType_GetNameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Boolean IsValid() =>
            PrimaryAssetTypeImplementation.PrimaryAssetType_IsValidImplementation(GetHandle());

        public override string ToString()
        {
            PrimaryAssetTypeImplementation.PrimaryAssetType_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        // @TODO
        // ExportTextItem
        // ImportTextItem
        // SerializeFromMismatchedTag
    }
}