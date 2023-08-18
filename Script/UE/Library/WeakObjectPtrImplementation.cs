using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class WeakObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_RegisterImplementation<T>(TWeakObjectPtr<T> InWeakObjectPtr, T InObject)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_UnRegisterImplementation(IntPtr InWeakObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_GetImplementation<T>(IntPtr InWeakObjectPtr, out T OutValue)
            where T : UObject;
    }
}