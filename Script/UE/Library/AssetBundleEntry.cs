using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FAssetBundleEntry
    {
        public Boolean IsValid() =>
            AssetBundleEntryImplementation.AssetBundleEntry_IsValidImplementation(GetHandle());

        public static Boolean operator ==(FAssetBundleEntry A, FAssetBundleEntry B) =>
            AssetBundleEntryImplementation.AssetBundleEntry_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FAssetBundleEntry A, FAssetBundleEntry B) =>
            AssetBundleEntryImplementation.AssetBundleEntry_InequalityImplementation(A.GetHandle(), B.GetHandle());
    }
}