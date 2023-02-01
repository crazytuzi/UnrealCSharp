using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class PrimaryAssetTypeImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetType_GetNameImplementation(FPrimaryAssetType InPrimaryAssetType,
            out FName OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetType_EqualityImplementation(FPrimaryAssetType A, FPrimaryAssetType B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean
            PrimaryAssetType_InequalityImplementation(FPrimaryAssetType A, FPrimaryAssetType B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetType_IsValidImplementation(FPrimaryAssetType InPrimaryAssetType);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetType_ToStringImplementation(FPrimaryAssetType InPrimaryAssetType,
            out FString OutValue);
    }
}