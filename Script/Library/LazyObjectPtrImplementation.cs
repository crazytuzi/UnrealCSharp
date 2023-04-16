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
        public static extern void LazyObjectPtr_UnRegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr)
            where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LazyObjectPtr_GetImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr, out T OutValue)
            where T : UObject;
    }
}