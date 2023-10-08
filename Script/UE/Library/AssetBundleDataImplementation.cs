using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class AssetBundleDataImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_FindEntryImplementation(IntPtr InAssetBundleData,
            FName SearchName, out FAssetBundleEntry OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_AddBundleAssetImplementation(IntPtr InAssetBundleData,
            FName BundleName, FSoftObjectPath AssetPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_ResetImplementation(IntPtr InAssetBundleData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void AssetBundleData_ToDebugStringImplementation(IntPtr InAssetBundleData,
            out FString OutValue);
    }
}