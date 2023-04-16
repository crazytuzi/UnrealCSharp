using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class PrimaryAssetIdImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetId_ParseTypeAndNameNameImplementation(FName TypeAndName,
            out FPrimaryAssetId OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetId_ParseTypeAndNameStringImplementation(FString TypeAndName,
            out FPrimaryAssetId OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetId_IsValidImplementation(FPrimaryAssetId InPrimaryAssetId);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetId_ToStringImplementation(FPrimaryAssetId InPrimaryAssetId,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PrimaryAssetId_FromStringImplementation(FString String, out FPrimaryAssetId OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetId_EqualityImplementation(FPrimaryAssetId A, FPrimaryAssetId B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PrimaryAssetId_InequalityImplementation(FPrimaryAssetId A, FPrimaryAssetId B);
    }
}