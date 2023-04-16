using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FAssetBundleData
    {
        public static Boolean operator ==(FAssetBundleData A, FAssetBundleData B) =>
            AssetBundleDataImplementation.AssetBundleData_EqualityImplementation(A, B);

        public static Boolean operator !=(FAssetBundleData A, FAssetBundleData B) =>
            AssetBundleDataImplementation.AssetBundleData_InequalityImplementation(A, B);

        public FAssetBundleEntry FindEntry(FName SearchName)
        {
            AssetBundleDataImplementation.AssetBundleData_FindEntryImplementation(this, SearchName, out var OutValue);

            return OutValue;
        }

        public void AddBundleAsset(FName BundleName, FSoftObjectPath AssetPath) =>
            AssetBundleDataImplementation.AssetBundleData_AddBundleAssetImplementation(this, BundleName, AssetPath);

        // @TODO
        // AddBundleAsset
        // AddBundleAssets
        // SetBundleAssets

        public void Reset() =>
            AssetBundleDataImplementation.AssetBundleData_ResetImplementation(this);

        // @TODO
        // ExportTextItem
        // ImportTextItem

        public FString ToDebugString()
        {
            AssetBundleDataImplementation.AssetBundleData_ToDebugStringImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}