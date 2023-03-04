using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FPrimaryAssetType
    {
        public FName GetName()
        {
            PrimaryAssetTypeImplementation.PrimaryAssetType_GetNameImplementation(this, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FPrimaryAssetType A, FPrimaryAssetType B) =>
            PrimaryAssetTypeImplementation.PrimaryAssetType_EqualityImplementation(A, B);

        public static Boolean operator !=(FPrimaryAssetType A, FPrimaryAssetType B) =>
            PrimaryAssetTypeImplementation.PrimaryAssetType_InequalityImplementation(A, B);

        public Boolean IsValid() =>
            PrimaryAssetTypeImplementation.PrimaryAssetType_IsValidImplementation(this);

        public override string ToString()
        {
            PrimaryAssetTypeImplementation.PrimaryAssetType_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        // @TODO
        // ExportTextItem
        // ImportTextItem
        // SerializeFromMismatchedTag
    }
}