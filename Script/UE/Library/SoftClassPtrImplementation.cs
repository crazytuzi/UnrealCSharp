using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class SoftClassPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_RegisterImplementation<T>(TSoftClassPtr<T> InSoftClassPtr,
            UClass InClass)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean SoftClassPtr_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_UnRegisterImplementation(IntPtr InSoftClassPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_GetImplementation(IntPtr InSoftClassPtr,
            out UClass OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SoftClassPtr_LoadSynchronousImplementation(IntPtr InSoftClassPtr,
            out UClass OutValue);
    }
}