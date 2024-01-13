using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class LazyObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool LazyObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T LazyObjectPtr_GetImplementation<T>(nint InLazyObjectPtr);
    }
}