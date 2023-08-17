using System;
using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class AssetBundleEntryImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleEntry_IsValidImplementation(IntPtr InAssetBundleEntry);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean AssetBundleEntry_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            AssetBundleEntry_InequalityImplementation(IntPtr A, IntPtr B);
    }
}