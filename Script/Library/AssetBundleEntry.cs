using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FAssetBundleEntry
    {
        public Boolean IsValid() =>
            AssetBundleEntryImplementation.AssetBundleEntry_IsValidImplementation(this);

        public static Boolean operator ==(FAssetBundleEntry A, FAssetBundleEntry B) =>
            AssetBundleEntryImplementation.AssetBundleEntry_EqualityImplementation(A, B);

        public static Boolean operator !=(FAssetBundleEntry A, FAssetBundleEntry B) =>
            AssetBundleEntryImplementation.AssetBundleEntry_InequalityImplementation(A, B);
    }
}