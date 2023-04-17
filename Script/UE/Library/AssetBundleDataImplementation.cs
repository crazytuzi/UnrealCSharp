using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class AssetBundleDataImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleData_EqualityImplementation(FAssetBundleData A, FAssetBundleData B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleData_InequalityImplementation(FAssetBundleData A, FAssetBundleData B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_FindEntryImplementation(FAssetBundleData InAssetBundleData,
            FName SearchName, out FAssetBundleEntry OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_AddBundleAssetImplementation(FAssetBundleData InAssetBundleData,
            FName BundleName, FSoftObjectPath AssetPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_ResetImplementation(FAssetBundleData InAssetBundleData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_ToDebugStringImplementation(FAssetBundleData InAssetBundleData,
            out FString OutValue);
    }
}