using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class LazyObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr, T InObject)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_UnRegisterImplementation(IntPtr InLazyObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_GetImplementation<T>(IntPtr InLazyObjectPtr, out T OutValue)
            where T : UObject;
    }
}