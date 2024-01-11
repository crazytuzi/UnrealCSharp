using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class LazyObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            IntPtr InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean LazyObjectPtr_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_UnRegisterImplementation(IntPtr InLazyObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object LazyObjectPtr_GetImplementation(IntPtr InLazyObjectPtr);
    }
}