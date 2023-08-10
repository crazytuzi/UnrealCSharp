using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;
using IntPtr = System.IntPtr;

namespace Script.Library
{
    public static class SoftObjectPathImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_ToStringImplementation(IntPtr InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetPathNameImplementation(IntPtr InSoftObjectPath,
            out FName OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetPathStringImplementation(IntPtr InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetSubPathStringImplementation(IntPtr InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetLongPackageNameImplementation(IntPtr InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_GetAssetNameImplementation(IntPtr InSoftObjectPath,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void
            SoftObjectPath_SetPathNameImplementation(IntPtr InSoftObjectPath, FName Path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_SetPathStringImplementation(IntPtr InSoftObjectPath,
            FString Path);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftObjectPath_ResetImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsValidImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsNullImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsAssetImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_IsSubobjectImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_EqualityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_InequalityImplementation(IntPtr A, IntPtr B);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupForPIEImplementation(IntPtr InSoftObjectPath);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupForPIEInstanceImplementation(IntPtr InSoftObjectPath,
            Int32 PIEInstance);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftObjectPath_FixupCoreRedirectsImplementation(IntPtr InSoftObjectPath);

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