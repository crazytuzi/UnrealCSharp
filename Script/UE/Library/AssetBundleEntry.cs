using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FAssetBundleEntry
    {
        public Boolean IsValid() =>
            AssetBundleEntryImplementation.AssetBundleEntry_IsValidImplementation(GetHandle());
    }
}