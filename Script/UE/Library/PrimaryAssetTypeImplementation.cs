using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class PrimaryAssetTypeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetType_GetNameImplementation(IntPtr InPrimaryAssetType,
            out FName OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetType_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            PrimaryAssetType_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetType_IsValidImplementation(IntPtr InPrimaryAssetType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetType_ToStringImplementation(IntPtr InPrimaryAssetType,
            out FString OutValue);
    }
}