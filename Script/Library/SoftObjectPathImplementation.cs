using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftObjectPathImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_ToStringImplementation(FSoftObjectPath InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetPathNameImplementation(FSoftObjectPath InSoftObjectPath,
            out FName OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetPathStringImplementation(FSoftObjectPath InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetSubPathStringImplementation(FSoftObjectPath InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetLongPackageNameImplementation(FSoftObjectPath InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetNameImplementation(FSoftObjectPath InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            SoftObjectPath_SetPathNameImplementation(FSoftObjectPath InSoftObjectPath, FName Path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_SetPathStringImplementation(FSoftObjectPath InSoftObjectPath,
            FString Path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_ResetImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsValidImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsNullImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsAssetImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsSubobjectImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_EqualityImplementation(FSoftObjectPath A, FSoftObjectPath B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_InequalityImplementation(FSoftObjectPath A, FSoftObjectPath B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupForPIEImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupForPIEInstanceImplementation(FSoftObjectPath InSoftObjectPath,
            Int32 PIEInstance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupCoreRedirectsImplementation(FSoftObjectPath InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 SoftObjectPath_GetCurrentTagImplementation();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Int32 SoftObjectPath_InvalidateTagImplementation();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetOrCreateIDForObjectImplementation(UObject Object,
            out FSoftObjectPath OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_AddPIEPackageNameImplementation(FName NewPIEPackageName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_ClearPIEPackageNamesImplementation();
    }
}