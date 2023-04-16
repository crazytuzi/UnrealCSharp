using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class AssetBundleEntryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleEntry_IsValidImplementation(FAssetBundleEntry InAssetBundleEntry);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleEntry_EqualityImplementation(FAssetBundleEntry A, FAssetBundleEntry B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            AssetBundleEntry_InequalityImplementation(FAssetBundleEntry A, FAssetBundleEntry B);
    }
}