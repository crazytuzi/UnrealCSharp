using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class WeakObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_RegisterImplementation<T>(TWeakObjectPtr<T> InWeakObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool WeakObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void WeakObjectPtr_UnRegisterImplementation(nint InWeakObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T WeakObjectPtr_GetImplementation<T>(nint InWeakObjectPtr);
    }
}