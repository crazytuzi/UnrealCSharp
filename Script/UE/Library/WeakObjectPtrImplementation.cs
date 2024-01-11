using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class WeakObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_RegisterImplementation<T>(TWeakObjectPtr<T> InWeakObjectPtr,
            IntPtr InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean WeakObjectPtr_IdenticalImplementation(IntPtr InA, IntPtr InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_UnRegisterImplementation(IntPtr InWeakObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Object WeakObjectPtr_GetImplementation(IntPtr InWeakObjectPtr);
    }
}