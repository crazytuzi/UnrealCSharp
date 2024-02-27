using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static class TLazyObjectPtrImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TLazyObjectPtr_RegisterImplementation<T>(TLazyObjectPtr<T> InLazyObjectPtr,
            nint InObject) where T : UObject;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool TLazyObjectPtr_IdenticalImplementation(nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void TLazyObjectPtr_UnRegisterImplementation(nint InLazyObjectPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T TLazyObjectPtr_GetImplementation<T>(nint InLazyObjectPtr);
    }
}